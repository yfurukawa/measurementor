/*!
 @file Item.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "Item.h"
#include <iostream>

namespace measurementor
{

Item::Item(ItemId itemId, Name itemName, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status, StatusCode statusCode,
           EstimatedTime totalEstimatedTime)
  : itemId_(itemId)
  , itemName_(itemName)
  , projectId_(projectId)
  , storyPoint_(storyPoint)
  , status_(status)
  , statusCode_(statusCode)
  , sprintId_(sprintId)
  , totalEstimatedTime_(totalEstimatedTime)
{
}

Point Item::reportStoryPoint(SprintId sprintId)
{
  if (this->isOpen() && sprintId_ == sprintId)
  {
    return storyPoint_;
  }

  return Point(0);
}

EstimatedTime Item::reportRemainingWorkTime(SprintId sprintId)
{
  if (this->isOpen() && sprintId_ == sprintId)
  {
    return totalEstimatedTime_;
  }

  return EstimatedTime(0);
}

std::string Item::createJson(const Timestamp& timestamp)
{
  JsonKey indexType("indexType");
  std::string type("Item");
  jsonCreator_.holdData(indexType, type);

  JsonKey tstamp("timestamp");
  jsonCreator_.holdData(tstamp, timestamp.get());

  JsonKey itemId("itemId");
  jsonCreator_.holdData(itemId, itemId_.get());

  JsonKey itemName("itemName");
  jsonCreator_.holdData(itemName, itemName_.get());

  JsonKey projectId("projectId");
  jsonCreator_.holdData(projectId, projectId_.get());

  JsonKey sprintId("sprintId");
  jsonCreator_.holdData(sprintId, sprintId_.get());

  JsonKey totalEstimatedTime("totalEstimatedTime");
  jsonCreator_.holdData(totalEstimatedTime, totalEstimatedTime_.get());

  JsonKey storyPoint("storyPoint");
  jsonCreator_.holdData(storyPoint, storyPoint_.get());

  JsonKey status("itemStatus");
  jsonCreator_.holdData(status, status_.get());

  JsonKey statusCode("itemStatusCode");
  jsonCreator_.holdData(statusCode, statusCode_.get());

  return jsonCreator_.createJson();
}

inline bool Item::isOpen()
{
  int closed(12);
  return statusCode_ != closed;
}

}  // namespace measurementor