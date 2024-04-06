/*!
 @file  MetricCalculator.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "IRepository.h"
#include "IRepositoryFactory.h"
#include "MetricCalculator.h"
#include "Task.h"

namespace measurementor
{

MetricCalculator::MetricCalculator()
  : repository_(IRepositoryFactory::getInstance()->createRepository())
  , chronos_(std::make_unique<Chronos>())
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
    calculateDuration(currentTask->second, previousTaskList[currentTask->first]);
  }
}

void MetricCalculator::calculateDuration(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask)
{
  nlohmann::json updateData;
  updateData["TaskId"] = 0;
  updateData["InProgressStartDate"] = nullptr;
  updateData["ReviewStartDate"] = nullptr;
  updateData["CompleteDate"] = nullptr;
  updateData["InProgressDuration"] = 0;
  updateData["ReviewDuration"] = 0;
  updateData["TotalDuration"] = 0;

  // Status is still New
  if (currentTask->statusCode_ == 1)
  {
    // Nothing to do
    return;
  }
  // Changed state from New to In Progress
  if (previousTask->statusCode_ == 1 && currentTask->statusCode_ == 7)
  {
    //UpdatedAt startDate{currentTask->updatedAt_};
    updateData["TaskId"] = currentTask->taskId_.get();
    updateData["InProgressStartDate"] = currentTask->updatedAt_.get();
    durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
    repository_->registerMetricsData(currentTask->taskId_, updateData);
  }
  
  // Changed state from In Progress To Review
  if (previousTask->statusCode_ == 7 && currentTask->statusCode_ == 15)
  {
    //UpdatedAt startDate{currentTask->updatedAt_};
    updateData["TaskId"] = currentTask->taskId_.get();
    updateData["ReviewStartDate"] = currentTask->updatedAt_.get();
    durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
    // TODO(yfurukawa) implement to stare Revire start date
    // TODO(yfurukawa) implement to calculate In-Progress duration
  }

    // Changed state from In Progress To Review
  if (currentTask->statusCode_ == 10 && (previousTask->statusCode_ == 15 || previousTask->statusCode_ < currentTask->statusCode_))
  {
    //UpdatedAt startDate{currentTask->updatedAt_};
    updateData["TaskId"] = currentTask->taskId_.get();
    updateData["CompleteDate"] = currentTask->updatedAt_.get();
    durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
    // TODO(yfurukawa) implement to stare Revire start date
    // TODO(yfurukawa) implement to calculate Review duration
    // TODO(yfurukawa) implement to calculate working time of this task
  }
}

}  // namespace measurementor