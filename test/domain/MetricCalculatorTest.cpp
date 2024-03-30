#include <memory>
#include <string>
#include "MetricCalculatorTest.h"
#include "MetricCalculatorSpy.h"
#include "../../src/domain/Task.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"
#include "nlohmann/json.hpp"

namespace measurementor
{
void MetricCalculatorTest::SetUp()
{
  sut = new MetricCalculatorSpy();
}

void MetricCalculatorTest::TearDown()
{
  delete sut;
}

TEST_F(MetricCalculatorTest, calculateDuration_ChangeStateFromNewToInProgress)
{
  std::map<TaskId, std::shared_ptr<Task>> currentTaskList;
  std::map<TaskId, std::shared_ptr<Task>> previousTaskList;
  currentTaskList.clear();
  previousTaskList.clear();

  currentTaskList.insert(std::make_pair(TaskId{10}, std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"In progress"}, StatusCode{7}, UpdatedAt{"2024-03-28T14:34:56Z"})));
  previousTaskList.insert(std::make_pair(TaskId{10}, std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"New"}, StatusCode{1}, UpdatedAt{"2024-03-28T12:34:56Z"})));

  nlohmann::json expected;
  expected["TaskId"] = 10;
  expected["InProgressStartDate"] = "2024-03-28T14:34:56Z";
  expected["ReviewStartDate"] = nullptr;
  expected["CompleteDate"] = nullptr;
  expected["InProgressDuration"] = 0;
  expected["ReviewDuration"] = 0;
  expected["TotalDuration"] = 0;
  
  sut->calculateMetrics(currentTaskList, previousTaskList);
  EXPECT_EQ(expected, sut->getDurationDataList()[TaskId{10}]);
}

}  // namespace measurementor