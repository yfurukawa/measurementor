/*!
 @file PtsDataCollector.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/

#include <utility>
#include "PtsDataCollector.h"
#include "Chronos.h"
#include "IAnalyzer.h"
#include "IAnalyzerFactory.h"
#include "IPts.h"
#include "IPtsFactory.h"
#include "IPreviousDataReader.h"
#include "IPreviousDataReaderFactory.h"
#include "Item.h"
#include "MetricCalculator.h"
#include "Project.h"
#include "Sprint.h"
#include "Task.h"

namespace measurementor
{

PtsDataCollector::PtsDataCollector()
  : ptsFactory_(IPtsFactory::getInstance())
  , pts_(ptsFactory_->createPts())
  , analyzer_(IAnalyzerFactory::getInstance()->createIAnalyzer())
  , chronos_(std::make_unique<::Chronos>())
  , previousDataReaderFactory_(IPreviousDataReaderFactory::getInstance())
  , previousDataReader_(previousDataReaderFactory_->createPreviousDataReader())
  , metricCalculator_(std::make_unique<MetricCalculator>())

{
  projectList_.clear();
  sprintList_.clear();
  itemList_.clear();
  taskList_.clear();
  previousTaskList_.clear();
  jsonObject_.clear();
}

PtsDataCollector::~PtsDataCollector()
{
  projectList_.clear();
  sprintList_.clear();
  itemList_.clear();
  taskList_.clear();
  previousTaskList_.clear();
  jsonObject_.clear();
}

void PtsDataCollector::collectAllData()
{
  collectProjectData();
  readPreviousTaskData();
  collectSprintData();
  collectItemData();
  collectTaskData();

  this->aggrigateData();
}

void PtsDataCollector::permanentProjectData()
{
  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    jsonObject_.push_back(std::move(project->second->createJson()));
  }

  for (auto json = begin(jsonObject_); json != end(jsonObject_); ++json)
  {
    analyzer_->registerMeasurementedData("project", *json);
  }
  // データを登録したことで不要になったデータは削除しておく
  jsonObject_.clear();
}

void PtsDataCollector::permanentSprintData()
{
  Timestamp timestamp(chronos_->nowIso8601ExtendedGmt());
  for (auto sprint = begin(sprintList_); sprint != end(sprintList_); ++sprint)
  {
    jsonObject_.push_back(std::move(sprint->second->createJson(timestamp)));
  }

  for (auto item = begin(itemList_); item != end(itemList_); ++item)
  {
    jsonObject_.push_back(std::move(item->second->createJson(timestamp)));
  }

  for (auto task = begin(taskList_); task != end(taskList_); ++task)
  {
    jsonObject_.push_back(std::move(task->second->createJson(timestamp)));
  }

  for (auto json = begin(jsonObject_); json != end(jsonObject_); ++json)
  {
    analyzer_->registerMeasurementedData("project_detail", *json);
  }
  // データを登録したことで不要になったデータは削除しておく
  jsonObject_.clear();
}

void PtsDataCollector::collectProjectData()
{
  std::list<std::map<std::string, std::string>> jsonObjectList;
  jsonObjectList.clear();

  // 分析するためにデータの取得日時が必要
  Timestamp timestamp(chronos_->nowIso8601ExtendedGmt());

  // PTSには、クローズした（非アクティブな）過去のプロジェクトも登録されているので、現状アクティブなプロジェクトのみを対象とする
  jsonObjectList = pts_->collectAllActiveProject();
  std::list<ProjectId> exclusiveProjects;

  for (auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json)
  {
    ProjectId projectId(std::stoi((*json)["projectId"]));
    Name projectName((*json)["projectName"]);
    ProjectId parentId(std::stoi((*json)["parentId"]));
    exclusiveProjects.push_back(parentId);
    projectList_.insert(std::make_pair(projectId, std::make_shared<Project>(projectId, projectName, parentId, timestamp)));
  }

  // 同じ親を持つプロジェクトが複数ある可能性があるので、重複している親プロジェクトのidを削除する
  exclusiveProjects.sort();
  exclusiveProjects.unique();

  // 親プロジェクトはSprint等を持たないので集計対象とする必要はないので削除する
  for (auto exclusive = begin(exclusiveProjects); exclusive != end(exclusiveProjects); ++exclusive)
  {
    for (auto project = begin(projectList_); project != end(projectList_);)
    {
      if (project->first == *exclusive)
      {
        project = projectList_.erase(project);
      }
      else
      {
        ++project;
      }
    }
  }
}

void PtsDataCollector::collectSprintData()
{
  std::list<std::map<std::string, std::string>> jsonObjectList;
  jsonObjectList.clear();

  // アクティブなプロジェクトのみのSprint情報を取得するには、プロジェクトIDを指定する必要があるので
  // 取得済みのプロジェクトに対して処理を行う
  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    jsonObjectList.merge(pts_->collectSprintInformation(project->first));
  }

  for (auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json)
  {
    ProjectId projectId(std::stoi((*json)["projectId"]));
    SprintId sprintId(std::stoi((*json)["sprintId"]));
    Name sprintName((*json)["sprintName"]);
    Status status((*json)["status"]);
    StartDate startDate((*json)["startDate"]);
    EndDate endDate((*json)["endDate"]);
    sprintList_.insert(std::make_pair(sprintId, std::make_shared<Sprint>(projectId, sprintId, sprintName, status, startDate, endDate)));
  }
}

void PtsDataCollector::collectItemData()
{
  std::list<std::map<std::string, std::string>> jsonObjectList;
  jsonObjectList.clear();

  // アクティブなプロジェクトのみのSprint情報を取得するには、プロジェクトIDを指定する必要があるので
  // 取得済みのプロジェクトに対して処理を行う
  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    jsonObjectList.merge(pts_->collectItemInformation(project->first));
  }

  for (auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json)
  {
    ProjectId projectId(std::stoi((*json)["projectId"]));
    SprintId sprintId(std::stoi((*json)["sprintId"]));
    ItemId itemId(std::stoi((*json)["itemId"]));
    Name itemName((*json)["itemName"]);
    Status status((*json)["status"]);
    StatusCode statusCode(std::stoi((*json)["statusCode"]));
    EstimatedTime totalEstimatedTime(std::stoi((*json)["totalEstimatedTime"]));
    Point storyPoint(std::stoi((*json)["storyPoint"]));
    itemList_.insert(std::make_pair(
      itemId, std::make_shared<Item>(itemId, itemName, projectId, sprintId, storyPoint, status, statusCode, totalEstimatedTime)));
  }
}

void PtsDataCollector::collectTaskData()
{
  std::list<std::map<std::string, std::string>> jsonObjectList;
  jsonObjectList.clear();

  // アクティブなプロジェクトのみのSprint情報を取得するには、プロジェクトIDを指定する必要があるので
  // 取得済みのプロジェクトに対して処理を行う
  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    jsonObjectList.merge(pts_->collectTaskInformation(project->first));
  }

  for (auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json)
  {
    ProjectId projectId(std::stoi((*json)["projectId"]));
    Name projectName((*json)["projectName"]);
    SprintId sprintId(std::stoi((*json)["sprintId"]));
    Name sprintName((*json)["sprintName"]);
    ItemId itemId(std::stoi((*json)["itemId"]));
    TaskId taskId(std::stoi((*json)["taskId"]));
    Name taskName((*json)["taskName"]);
    Status status((*json)["status"]);
    StatusCode statusCode(std::stoi((*json)["statusCode"]));
    Author author((*json)["author"]);
    EstimatedTime estimatedTime(std::stoi((*json)["estimatedTime"]));
    Assignee assignee((*json)["assignee"]);
    UpdatedAt updatedAt((*json)["updatedAt"]);

    taskList_.insert(std::make_pair(taskId, std::make_shared<Task>(projectId, projectName, sprintId, sprintName, itemId, taskId, taskName, author, estimatedTime,
                                                                   assignee, status, statusCode, updatedAt)));
  }

  metricCalculator_->calculateMetrics(taskList_, previousTaskList_);
}

void PtsDataCollector::readPreviousTaskData()
{
  std::list<std::map<std::string, std::string>> jsonObjectList;
  jsonObjectList.clear();

  // 前回値データはプロジェクトID毎にファイルが別れているのでプロジェクト毎に読み込み、マージする
  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    jsonObjectList.merge(previousDataReader_->preparePreviousTaskData(project->first));
  }

  for (auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json)
  {
    ProjectId projectId(std::stoi((*json)["projectId"]));
    Name projectName((*json)["projectName"]);
    SprintId sprintId(std::stoi((*json)["sprintId"]));
    Name sprintName((*json)["sprintName"]);
    ItemId itemId(std::stoi((*json)["itemId"]));
    TaskId taskId(std::stoi((*json)["taskId"]));
    Name taskName((*json)["taskName"]);
    Status status((*json)["status"]);
    StatusCode statusCode(std::stoi((*json)["statusCode"]));
    Author author((*json)["author"]);
    EstimatedTime estimatedTime(std::stoi((*json)["estimatedTime"]));
    Assignee assignee((*json)["assignee"]);
    UpdatedAt updatedAt((*json)["updatedAt"]);
    previousTaskList_.insert(std::make_pair(taskId, std::make_shared<Task>(projectId, projectName, sprintId, sprintName, itemId, taskId, taskName, author,
                                                                           estimatedTime, assignee, status, statusCode, updatedAt)));
  }
}

void PtsDataCollector::aggrigateData()
{
  this->aggrigateStoryPoint();
  this->aggrigateRemainingWorkTime();
}

void PtsDataCollector::aggrigateStoryPoint()
{
  Point remainingPointforSprint(0);
  Point remainingPointforProject(0);

  for (auto sprint = begin(sprintList_); sprint != end(sprintList_); ++sprint)
  {
    remainingPointforSprint = remainingPointforSprint -
                              remainingPointforSprint;  // StrongTypeは初期化後に代入できないので、自分自身の差分を取ることで値を0にしている
    for (auto item = begin(itemList_); item != end(itemList_); ++item)
    {
      remainingPointforSprint = remainingPointforSprint + item->second->reportStoryPoint(sprint->first);
    }
    sprint->second->registerStoryPoint(remainingPointforSprint);
  }

  for (auto project = begin(projectList_); project != end(projectList_); ++project)
  {
    remainingPointforProject = remainingPointforProject - remainingPointforProject;
    for (auto sprint = begin(sprintList_); sprint != end(sprintList_); ++sprint)
    {
      remainingPointforProject = remainingPointforProject + sprint->second->reportStoryPoint(project->first);
    }
    project->second->registerStoryPoint(remainingPointforProject);
  }
}

void PtsDataCollector::aggrigateRemainingWorkTime()
{
  for (auto sprint = begin(sprintList_); sprint != end(sprintList_); ++sprint)
  {
    sprint->second->aggrigateRemainingWorkTime(itemList_);
  }
}

}  // namespace measurementor
