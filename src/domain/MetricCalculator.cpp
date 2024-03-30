/*!
 @file  MetricCalculator.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "MetricCalculator.h"
#include "Task.h"

namespace measurementor
{

MetricCalculator::MetricCalculator()
  : chronos_(std::make_unique<Chronos>())
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

  // Status is New
  if (currentTask->statusCode_ == 1)
  {
    // Nothing to do
    return;
  }
  // Changed state from New to In Progress
  if (currentTask->statusCode_ == 7 && previousTask->statusCode_ == 1)
  {
    //UpdatedAt startDate{currentTask->updatedAt_};
    updateData["TaskId"] = currentTask->taskId_.get();
    updateData["InProgressStartDate"] = currentTask->updatedAt_.get();
    durationDataList_.insert(std::make_pair(currentTask->taskId_, updateData));
  }
}

}  // namespace measurementor