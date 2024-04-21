#include <string>
#include "SprintTest.h"
#include "../../src/domain/Sprint.h"

namespace measurementor
{
void SprintTest::SetUp() {}

void SprintTest::TearDown()
{
  delete sut;
}

TEST_F(SprintTest, createJson_noAssignedItem)
{
  ProjectId projectId(10);
  SprintId sprintId(1);
  Name sprintName("Test Sprint");
  Status status("open");
  StartDate startDate("2024-02-23T12:34:56+09:00");
  EndDate endDate("2024-02-25T12:34:56+09:00");

  Timestamp tstamp("2024-02-25T12:34:56+09:00");

  sut = new Sprint(projectId, sprintId, sprintName, status, startDate, endDate);

  std::string expected(
    R"({"endDate":"2024-02-25T12:34:56+09:00","indexType":"Sprint","projectId":10,"remainingWorkTime":0.0,"sprintId":1,"sprintName":"Test Sprint","startDate":"2024-02-23T12:34:56+09:00","status":"open","timestamp":"2024-02-25T12:34:56+09:00","totalStoryPoint":0})");

  EXPECT_EQ(expected, sut->createJson(tstamp));
}

}  // namespace measurementor