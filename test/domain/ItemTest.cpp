#include <memory>
#include <string>
#include "ItemTest.h"
#include "../../src/domain/Item.h"

namespace measurementor
{
void ItemTest::SetUp() {}

void ItemTest::TearDown()
{
  delete sut;
}

TEST_F(ItemTest, createJson_noAssignedTask)
{
  ItemId itemId(1);
  Name itemName("Test Item");
  ProjectId projectId(10);
  SprintId sprintId(12);
  Point storyPoint(3);
  Status status("New");
  StatusCode statusCode(1);
  EstimatedTime totalEstimatedTime(5.5);

  Timestamp tstamp("2024-02-28T12:34:56.123");

  sut = new Item(itemId, itemName, projectId, sprintId, storyPoint, status, statusCode, totalEstimatedTime);

  std::string expected(
    R"({"indexType":"Item","itemId":1,"itemName":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"timestamp":"2024-02-28T12:34:56.123","totalEstimatedTime":5.5})");

  EXPECT_EQ(expected, sut->createJson(tstamp));
}

}  // namespace measurementor