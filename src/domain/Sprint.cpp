/*!
 @file Sprint.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/

#include "Sprint.h"
#include "Item.h"
#include "Task.h"

namespace measurementor
{

Sprint::Sprint(ProjectId projectId, SprintId sprintId, Name sprintName, Status status, StartDate startDate, EndDate endDate)
  : sprintId_(sprintId)
  , sprintName_(sprintName)
  , projectId_(projectId)
  , totalPoint_(0)
  , status_(status)
  , startDate_(startDate)
  , endDate_(endDate)
  , remainingEstimatedTime_(0)
{
}

void Sprint::aggrigateRemainingWorkTime(std::map<ItemId, std::shared_ptr<Item>> itemList)
{
  for (auto item = begin(itemList); item != end(itemList); ++item)
  {
    remainingEstimatedTime_ = remainingEstimatedTime_ + item->second->reportRemainingWorkTime(sprintId_);
  }
}

Point Sprint::reportStoryPoint(ProjectId blongingProject)
{
  if (status_.get() == "closed" || projectId_ != blongingProject)
  {
    return Point(0);
  }
  return totalPoint_;
}

void Sprint::registerStoryPoint(Point remainingStoryPint)
{
  totalPoint_ = remainingStoryPint;
}

std::string Sprint::createJson(const Timestamp& timestamp)
{
  JsonKey indexType("indexType");
  std::string type("Sprint");
  jsonCreator_.holdData(indexType, type);

  JsonKey tstamp("timestamp");
  jsonCreator_.holdData(tstamp, timestamp.get());

  JsonKey sprintId("sprintId");
  jsonCreator_.holdData(sprintId, sprintId_.get());

  JsonKey sprintName("sprintName");
  jsonCreator_.holdData(sprintName, sprintName_.get());

  JsonKey startDate("startDate");
  jsonCreator_.holdData(startDate, startDate_.get());

  JsonKey endDate("endDate");
  jsonCreator_.holdData(endDate, endDate_.get());

  JsonKey projectId("projectId");
  jsonCreator_.holdData(projectId, projectId_.get());

  JsonKey totalStoryPoint("totalStoryPoint");
  jsonCreator_.holdData(totalStoryPoint, totalPoint_.get());

  JsonKey status("sprintStatus");
  jsonCreator_.holdData(status, status_.get());

  JsonKey remainingWorkTime("remainingWorkTime");
  jsonCreator_.holdData(remainingWorkTime, remainingEstimatedTime_.get());

  return jsonCreator_.createJson();
}

}  // namespace measurementor
