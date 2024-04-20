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

// タスクが新規から進行中に変化した場合
TEST_F(MetricCalculatorTest, checkTransit_ChangeStateFromNewToInProgress)
{
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"In progress"}, StatusCode{7}, UpdatedAt{"2024-03-28T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"New"}, StatusCode{1}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["taskId"] = 10;
  expected["taskName"] = "TestTask";
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

// タスクが進行中からレビュー中に変化した場合
TEST_F(MetricCalculatorTest, checkTransit_ChangeStateFromInProgressToReview)
{
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Review"}, StatusCode{15}, UpdatedAt{"2024-03-29T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"In progress"}, StatusCode{7}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["taskId"] = 10;
  expected["taskName"] = "TestTask";
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

TEST_F(MetricCalculatorTest, checkTransit_ChangeStateFromReviewToClosed)
{
  std::shared_ptr<Task> currentTask;
  std::shared_ptr<Task> previousTask;

  currentTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Closed"}, StatusCode{12}, UpdatedAt{"2024-03-29T14:34:56Z"});
  previousTask = std::make_shared<Task>(ProjectId{1}, SprintId{2}, ItemId{3}, TaskId{10}, Name{"TestTask"}, Author{""}, EstimatedTime{0},
       Assignee{"Assignee"}, Status{"Review"}, StatusCode{15}, UpdatedAt{"2024-03-28T12:34:56Z"});

  nlohmann::json expected;
  expected["taskId"] = 10;
  expected["taskName"] = "TestTask";
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

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_15min)
{
  ::ISO8601String   endDate("2014-04-06T12:34:59Z");
  ::ISO8601String startDate("2014-04-06T12:20:00Z");
  EXPECT_DOUBLE_EQ(0.25, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_EQ_15min)
{
  ::ISO8601String   endDate("2014-04-06T12:35:00Z");
  ::ISO8601String startDate("2014-04-06T12:20:00Z");
  EXPECT_EQ(0.25, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_30min)
{
  ::ISO8601String   endDate("2014-04-06T12:49:59Z");
  ::ISO8601String startDate("2014-04-06T12:20:00Z");
  EXPECT_DOUBLE_EQ(0.5, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_EQ_30min)
{
  ::ISO8601String   endDate("2014-04-06T12:50:00Z");
  ::ISO8601String startDate("2014-04-06T12:20:00Z");
  EXPECT_EQ(0.5, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_45min)
{
  ::ISO8601String   endDate("2014-04-06T12:54:59Z");
  ::ISO8601String startDate("2014-04-06T12:10:00Z");
  EXPECT_DOUBLE_EQ(0.75, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_EQ_45min)
{
  ::ISO8601String   endDate("2014-04-06T12:55:00Z");
  ::ISO8601String startDate("2014-04-06T12:10:00Z");
  EXPECT_EQ(0.75, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_60min)
{
  ::ISO8601String   endDate("2014-04-06T12:59:59Z");
  ::ISO8601String startDate("2014-04-06T12:00:00Z");
  EXPECT_DOUBLE_EQ(1.0, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_EQ_60min)
{
  ::ISO8601String   endDate("2014-04-06T13:20:00Z");
  ::ISO8601String startDate("2014-04-06T12:20:00Z");
  EXPECT_EQ(1.0, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_1H_15min)
{
  ::ISO8601String   endDate("2014-04-06T13:15:00Z");
  ::ISO8601String startDate("2014-04-06T12:00:00Z");
  EXPECT_DOUBLE_EQ(1.25, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_LE_1H_30min)
{
  ::ISO8601String   endDate("2014-04-06T13:30:00Z");
  ::ISO8601String startDate("2014-04-06T12:00:00Z");
  EXPECT_EQ(1.5, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_SameDay_Over_several_hours)
{
  ::ISO8601String   endDate("2014-04-06T14:18:03Z");
  ::ISO8601String startDate("2014-04-06T12:00:00Z");
  EXPECT_EQ(2.5, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_passed_several_days)
{
  ::ISO8601String   endDate("2014-04-04T14:18:03Z");
  ::ISO8601String startDate("2014-04-01T13:00:00Z");
  EXPECT_EQ(28.5, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_passed_several_days_and_several_weekend)
{
  ::ISO8601String   endDate("2024-04-22T04:00:00Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(135.0, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, calculateDuration_passed_several_days_and_several_weekend_sunday_work)
{
  ::ISO8601String   endDate("2024-04-21T04:00:00Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(135.0, sut->calculateDuration(startDate, endDate));
}

TEST_F(MetricCalculatorTest, passedWeekends_no_weekend)
{
  ::ISO8601String   endDate("2024-04-05T05:18:03Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(0, sut->passedWeekends(startDate, endDate));
}

TEST_F(MetricCalculatorTest, passedWeekends_one_weekend_passed)
{
  ::ISO8601String   endDate("2024-04-08T06:18:03Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(2, sut->passedWeekends(startDate, endDate));
}

TEST_F(MetricCalculatorTest, passedWeekends_one_weekend_but_SundayWork)
{
  ::ISO8601String   endDate("2024-04-07T06:18:03Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(1, sut->passedWeekends(startDate, endDate));
}

TEST_F(MetricCalculatorTest, passedWeekends_several_weekend_passed)
{
  ::ISO8601String   endDate("2024-04-22T06:18:03Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(6, sut->passedWeekends(startDate, endDate));
}

TEST_F(MetricCalculatorTest, passedWeekends_several_weekend_but_SundayWork)
{
  ::ISO8601String   endDate("2024-04-21T06:18:03Z");
  ::ISO8601String startDate("2024-04-01T04:00:00Z");
  EXPECT_EQ(5, sut->passedWeekends(startDate, endDate));
}

}  // namespace measurementor