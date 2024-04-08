#include "MetricCalculatorSpy.h"

namespace measurementor
{

void MetricCalculatorSpy::calculateMetrics(std::map<TaskId, std::shared_ptr<Task>> currentTaskList, std::map<TaskId, std::shared_ptr<Task>> previousTaskList)
{
  MetricCalculator::calculateMetrics(currentTaskList, previousTaskList);
}

void MetricCalculatorSpy::checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask, std::string timestamp)
{
  MetricCalculator::checkTransit(currentTask, previousTask, timestamp);
}

double MetricCalculatorSpy::calculateDuration(::ISO8601String startDate, ::ISO8601String endDate)
{
  return MetricCalculator::calculateDuration(startDate, endDate);
}

std::uint_fast16_t MetricCalculatorSpy::passedWeekends(::ISO8601String startDate, ::ISO8601String endDate)
{
  return MetricCalculator::passedWeekends(startDate, endDate);
}

std::map<TaskId, nlohmann::json> MetricCalculatorSpy::getDurationDataList()
{
    return MetricCalculator::durationDataList_;
}

}
