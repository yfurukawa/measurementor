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
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"In progress"}, StatusCode{7}, UpdatedAt{"2024-03-28T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"New"}, StatusCode{1}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["TaskId"] = 10;
  expected["InProgressStartDate"] = "2024-03-28T14:34:56Z";
  expected["ReviewStartDate"] = nullptr;
  expected["CloseDate"] = nullptr;
  expected["InProgressDuration"] = 0;
  expected["ReviewDuration"] = 0;
  expected["TotalDuration"] = 0;
  std::string expectedTimestamp("2024-04-06T12:34:56Z");
  expected["timestamp"] = expectedTimestamp;
  sut->checkTransit(currentTask, previousTask, expectedTimestamp);
  EXPECT_EQ(expected, sut->getDurationDataList()[TaskId{10}]);
}

TEST_F(MetricCalculatorTest, calculateDuration_ChangeStateFromInProgressToReview)
{
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Review"}, StatusCode{15}, UpdatedAt{"2024-03-29T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"In progress"}, StatusCode{7}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["TaskId"] = 10;
  expected["InProgressStartDate"] = nullptr;
  expected["ReviewStartDate"] = "2024-03-29T14:34:56Z";
  expected["CloseDate"] = nullptr;
  expected["InProgressDuration"] = 0;
  expected["ReviewDuration"] = 0;
  expected["TotalDuration"] = 0;
  std::string expectedTimestamp("2024-04-06T12:34:56Z");
  expected["timestamp"] = expectedTimestamp;
  sut->checkTransit(currentTask, previousTask, expectedTimestamp);
  EXPECT_EQ(expected, sut->getDurationDataList()[TaskId{10}]);
}

TEST_F(MetricCalculatorTest, calculateDuration_ChangeStateToClosed)
{
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Closed"}, StatusCode{12}, UpdatedAt{"2024-03-29T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Review"}, StatusCode{15}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["TaskId"] = 10;
  expected["InProgressStartDate"] = nullptr;
  expected["ReviewStartDate"] = nullptr;
  expected["CloseDate"] = "2024-03-29T14:34:56Z";
  expected["InProgressDuration"] = 0;
  expected["ReviewDuration"] = 0;
  expected["TotalDuration"] = 0;
  std::string expectedTimestamp("2024-04-06T12:34:56Z");
  expected["timestamp"] = expectedTimestamp;
  sut->checkTransit(currentTask, previousTask, expectedTimestamp);
  EXPECT_EQ(expected, sut->getDurationDataList()[TaskId{10}]);
}


}  // namespace measurementor