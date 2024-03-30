#include "MetricCalculatorSpy.h"

namespace measurementor
{

void MetricCalculatorSpy::calculateMetrics(std::map<TaskId, std::shared_ptr<Task>> currentTaskList, std::map<TaskId, std::shared_ptr<Task>> previousTaskList)
{
  MetricCalculator::calculateMetrics(currentTaskList, previousTaskList);
}

std::map<TaskId, nlohmann::json> MetricCalculatorSpy::getDurationDataList()
{
    return durationDataList_;
}

}
