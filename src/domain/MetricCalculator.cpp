/*!
 @file  MetricCalculator.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
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
    checkTransit(currentTask->second, previousTaskList[currentTask->first], chronos_->nowIso8601ExtendedGmt());
  }

  for (auto json = begin(durationDataList_); json != end(durationDataList_); ++json)
  {
    analyzer_->registerMeasurementedData((json->second).dump());
  }
  // データを登録したことで不要になったデータは削除しておく
  durationDataList_.clear();
}

void MetricCalculator::checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask, std::string timestamp)
{
  nlohmann::json updateData;
  updateData["TaskId"] = 0;
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
  updateData["TaskId"] = currentTask->taskId_.get();
  updateData["InProgressStartDate"] = currentTask->updatedAt_.get();
  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
  repository_->registerMetricsData(currentTask->taskId_, updateData);
}

void MetricCalculator::transitFromInProgressToReview(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  updateData["TaskId"] = currentTask->taskId_.get();
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
  updateData["TaskId"] = currentTask->taskId_.get();
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

  repository_->updateMetricsData(currentTask->taskId_, updateData);
  durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
}

void MetricCalculator::transitFromInProgressToClose(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  updateData["TaskId"] = currentTask->taskId_.get();
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
  long long difference = (chronos_->convertToTime_t(endDate) - chronos_->convertToTime_t(startDate));
  int differenceHour(difference / 3600);

  return differenceHour + roundDecimal((difference - differenceHour * 3600) / 3600.0);
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

}  // namespace measurementor