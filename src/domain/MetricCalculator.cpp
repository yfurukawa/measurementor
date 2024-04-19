/*!
 @file  MetricCalculator.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <ctime>
#include "IAnalyzer.h"
#include "IAnalyzerFactory.h"
#include "IRepository.h"
#include "IRepositoryFactory.h"
#include "MetricCalculator.h"
#include "Task.h"

namespace measurementor
{

MetricCalculator::MetricCalculator()
  : repository_(IRepositoryFactory::getInstance()->createRepository())
  , chronos_(std::make_unique<::Chronos>())
  , analyzer_(IAnalyzerFactory::getInstance()->createIAnalyzer())
{
  currentTaskList_.clear();
  previousTaskList_.clear();
  durationDataList_.clear();
}

void MetricCalculator::calculateMetrics(std::map<TaskId, std::shared_ptr<Task>> currentTaskList,
                                        std::map<TaskId, std::shared_ptr<Task>> previousTaskList)
{
  for (auto currentTask = begin(currentTaskList); currentTask != end(currentTaskList); ++currentTask)
  {
    if (previousTaskList.find(currentTask->first) != previousTaskList.end())
    {
      checkTransit(currentTask->second, previousTaskList[currentTask->first], chronos_->nowIso8601ExtendedGmt());
    }
  }

  for (auto json = begin(durationDataList_); json != end(durationDataList_); ++json)
  {
    analyzer_->registerMeasurementedData("project_detail_metrics", (json->second).dump());
  }
  // データを登録したことで不要になったデータは削除しておく
  durationDataList_.clear();
}

void MetricCalculator::checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask, std::string timestamp)
{
  nlohmann::json updateData;
  updateData["taskId"] = 0;
  updateData["InProgressStartDate"] = nullptr;
  updateData["ReviewStartDate"] = nullptr;
  updateData["CloseDate"] = nullptr;
  updateData["InProgressDuration"] = 0;
  updateData["ReviewDuration"] = 0;
  updateData["TotalDuration"] = 0;
  updateData["timestamp"] = timestamp;
  // Status is still New
  if (currentTask->statusCode_ == 1)
  {
    // Nothing to do
    return;
  }
  // Changed state from New to In Progress
  if (previousTask->statusCode_ == 1 && currentTask->statusCode_ == 7)
  {
    transitFromNewToInProgress(updateData, currentTask);
  }
  
  // Changed state from In Progress to Review
  if (previousTask->statusCode_ == 7 && currentTask->statusCode_ == 15)
  {
    transitFromInProgressToReview(updateData, currentTask, previousTask);
  }

  // Changed state from Review to Close
  if (previousTask->statusCode_ == 15 && currentTask->statusCode_ == 12)
  {
    transitFromReviewToClose(updateData, currentTask, previousTask);
  }
  
  if (previousTask->statusCode_ == 7 && currentTask->statusCode_ == 12)
  {
    transitFromInProgressToClose(updateData, currentTask, previousTask);
  }

}

void MetricCalculator::transitFromNewToInProgress(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask)
{
  updateData["taskId"] = currentTask->taskId_.get();
  updateData["taskName"] = currentTask->taskName_.get();
  updateData["InProgressStartDate"] = currentTask->updatedAt_.get();
  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
  repository_->registerMetricsData(currentTask->taskId_, updateData);
}

void MetricCalculator::transitFromInProgressToReview(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  updateData["taskId"] = currentTask->taskId_.get();
  updateData["taskName"] = currentTask->taskName_.get();
  updateData["ReviewStartDate"] = currentTask->updatedAt_.get();
      
  auto resultInProgress = repository_->getStarDateOnInProgress(currentTask->taskId_);
  if (resultInProgress)
  {
    // DB上のデータを更新するjsonに日時を入れ直さないとデータが無くなってしまう
    updateData["InProgressStartDate"] = resultInProgress.value().get();

    UpdatedAt startDate(resultInProgress.value());
    ::ISO8601String start{startDate.get()};
    ::ISO8601String end{currentTask->updatedAt_.get()};  // this is start date of review.

    auto duration = chronos_->convertToTime_t(end) - chronos_->convertToTime_t(start);
    updateData["InProgressDuration"] = duration / 3600;
  }
  repository_->updateMetricsData(currentTask->taskId_, updateData);
  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
}

void MetricCalculator::transitFromReviewToClose(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  updateData["taskId"] = currentTask->taskId_.get();
  updateData["taskName"] = currentTask->taskName_.get();
  updateData["CloseDate"] = currentTask->updatedAt_.get();
  updateData["InProgressDuration"] = repository_->getInProgressDuration(currentTask->taskId_);
  
  auto resultInProgress = repository_->getStarDateOnInProgress(currentTask->taskId_);
  if (resultInProgress)
  {
    // DB上のデータを更新するjsonに日時を入れ直さないとデータが無くなってしまう
    updateData["InProgressStartDate"] = resultInProgress.value().get();

    // In Progressになった日時と完了日時の差によってタスクの完了に掛かった時間を算出する
    ::ISO8601String start{resultInProgress.value().get()};
    ::ISO8601String end{currentTask->updatedAt_.get()};

    auto duration = chronos_->convertToTime_t(end) - chronos_->convertToTime_t(start);
    updateData["TotalDuration"] = duration / 3600;
  }

  auto resultReview = repository_->getStarDateOnReview(currentTask->taskId_);
  if (resultReview)
  {
    updateData["ReviewStartDate"] = resultReview.value().get();

    UpdatedAt reviewStartDate(resultReview.value());
    ::ISO8601String start{reviewStartDate.get()};
    ::ISO8601String end{currentTask->updatedAt_.get()};  // this is close date.

    auto duration = chronos_->convertToTime_t(end) - chronos_->convertToTime_t(start);
    updateData["ReviewDuration"] = duration / 3600;
  }

  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
  repository_->deleteMetricsData(currentTask->taskId_);
}

void MetricCalculator::transitFromInProgressToClose(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  updateData["taskId"] = currentTask->taskId_.get();
  updateData["taskName"] = currentTask->taskName_.get();
  updateData["CloseDate"] = currentTask->updatedAt_.get();
  
  auto resultInProgress = repository_->getStarDateOnInProgress(currentTask->taskId_);
  if (resultInProgress)
  {
    // DB上のデータを更新するjsonに日時を入れ直さないとデータが無くなってしまう
    updateData["InProgressStartDate"] = resultInProgress.value().get();

    UpdatedAt startDate(resultInProgress.value());
    ::ISO8601String start{startDate.get()};
    ::ISO8601String end{currentTask->updatedAt_.get()};  // this is close date.

    auto duration = chronos_->convertToTime_t(end) - chronos_->convertToTime_t(start);
    updateData["InProgressDuration"] = duration / 3600;
  }
  repository_->updateMetricsData(currentTask->taskId_, updateData);
  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
}

double MetricCalculator::calculateDuration(::ISO8601String startDate, ::ISO8601String endDate)
{
  long difference = (chronos_->convertToTime_t(endDate) - chronos_->convertToTime_t(startDate));
  std::uint_fast32_t differenceHour(difference / 3600);

  // 日付を跨いだ場合、17時から翌朝8時までの15時間は時間集計の対象外とする。
  // 週末の土日は更に8時から17時の9時間分も対象外とする。
  return differenceHour + roundDecimal((difference - differenceHour * 3600) / 3600.0) - passedDays(startDate, endDate) * 15 - passedWeekends(startDate, endDate) * 9;
}

double MetricCalculator::roundDecimal(double decimal)
{
  if (decimal == 0.0)
  {
    return 0.0;
  }
  else if (decimal <= 0.25)
  {
    return 0.25;
  }
  else if ((0.25 < decimal) && (decimal <= 0.5))
  {
    return 0.5;
  }
  else if ((0.5 < decimal) && (decimal <= 0.75))
  {
    return 0.75;
  }
  else
  {
    return 1.0;
  }
}

std::uint_fast32_t MetricCalculator::passedDays(::ISO8601String startDate, ::ISO8601String endDate)
{
  std::time_t start_t = chronos_->convertToTime_t(startDate);
  std::time_t end_t   = chronos_->convertToTime_t(endDate);
  std::uint_fast16_t yday[] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

  // time_tに変換した段階でGMTを表す日時になっているので、tmにする際にはローカルタイムとして扱うことで
  // GMTのtmを作り出す
  tm start = *std::localtime(&start_t);
  tm end   = *std::localtime(&end_t);
  std::uint_fast16_t start_yday = yday[start.tm_mon] + start.tm_mday;
  std::uint_fast16_t end_yday   = yday[end.tm_mon] + end.tm_mday;

  return end_yday - start_yday;
}

std::uint_fast16_t MetricCalculator::passedWeekends(::ISO8601String startDate, ::ISO8601String endDate)
{
  // 金曜日を起点にして考えた時に、以下の条件に当てはまる場合に週末の経過数が1以上になる
  // 3以上の場合（週末に休日出勤すれば、経過日数は2以下、休日出勤をしていなければ最低3日経過することになる）
  // 経過日数が3日以上で、且つ経過日数を7で割った数の整数値+1が週末を経過した数
  std::time_t start_t = chronos_->convertToTime_t(startDate);
  std::time_t end_t   = chronos_->convertToTime_t(endDate);
  tm start = *std::localtime(&start_t);
  tm end = *std::localtime(&end_t);

  std::uint_fast16_t duration = passedDays(startDate, endDate);
  
  // 開始曜日から経過日数後の曜日が最初の金曜日までであれば週末は経過していない
  if (start.tm_wday + duration <= 5)
  {
    return 0;
  }

  std::uint_fast16_t durationOptimized(duration - 5 - start.tm_wday);
  uint_fast16_t numberOfPassedWeekend((durationOptimized / 7 + 1) * 2);

  // 終了日が日曜の場合、日曜日分は考慮する必要がないので、週末日数から除外する
  if (end.tm_wday == 0)
  {
    --numberOfPassedWeekend;
  }

  return numberOfPassedWeekend;

}

}  // namespace measurementor
