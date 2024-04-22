/*!
 @file Task.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/

#include "Task.h"

namespace measurementor
{

Task::Task(ProjectId projectId, Name projectName, SprintId sprintId, Name sprintName, ItemId itemId, TaskId taskId, Name taskName, Author author, EstimatedTime estimatedTime,
           Assignee assignee, Status status, StatusCode statusCode, UpdatedAt updatedAt)
  : projectId_(projectId)
  , projectName_(projectName)
  , sprintId_(sprintId)
  , sprintName_(sprintName)
  , itemId_(itemId)
  , taskId_(taskId)
  , taskName_(taskName)
  , author_(author)
  , estimatedTime_(estimatedTime)
  , assignee_(assignee)
  , status_(status)
  , statusCode_(statusCode)
  , updatedAt_(updatedAt)
{
}

std::string Task::createJson(Timestamp timestamp)
{
  JsonKey indexType("indexType");
  std::string type("Task");
  jsonCreator_.holdData(indexType, type);

  JsonKey tstamp("timestamp");
  jsonCreator_.holdData(tstamp, timestamp.get());

  JsonKey pid("projectId");
  jsonCreator_.holdData(pid, projectId_.get());

  JsonKey projectName("projectName");
  jsonCreator_.holdData(projectName, projectName_.get());

  JsonKey sid("sprintId");
  jsonCreator_.holdData(sid, sprintId_.get());

  JsonKey sprintName("sprintName");
  jsonCreator_.holdData(sprintName, sprintName_.get());

  JsonKey id("taskId");
  jsonCreator_.holdData(id, taskId_.get());

  JsonKey taskName("taskName");
  jsonCreator_.holdData(taskName, taskName_.get());

  JsonKey author("author");
  jsonCreator_.holdData(author, author_.get());

  JsonKey itemId("itemId");
  jsonCreator_.holdData(itemId, itemId_.get());

  JsonKey estimatedTime("estimatedTime");
  jsonCreator_.holdData(estimatedTime, estimatedTime_.get());

  JsonKey assignee("assignee");
  jsonCreator_.holdData(assignee, assignee_.get());

  JsonKey status("status");
  jsonCreator_.holdData(status, status_.get());

  JsonKey statusCode("statusCode");
  jsonCreator_.holdData(statusCode, statusCode_.get());

  JsonKey updatedAt("updatedAt");
  jsonCreator_.holdData(updatedAt, updatedAt_.get());

  return jsonCreator_.createJson();
}

bool Task::isOpen()
{
  int closed(12);
  return statusCode_ != closed;
}

}  // namespace measurementor
