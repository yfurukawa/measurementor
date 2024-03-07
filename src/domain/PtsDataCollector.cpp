#include "Chronos.h"
#include "PtsDataCollector.h"
#include "../pts/openproject/OpenProjectFactory.h"   // TODO
#include "../pts/openproject/OpenProject.h"          // TODO
#include "../analyzer/elasticsearch/ElasticsearchFactory.h"
#include "../analyzer/elasticsearch/Elasticsearch.h"
#include "Project.h"
#include "Sprint.h"
#include "Item.h"
#include "Task.h"
#include <iostream>

namespace measurementor
{

PtsDataCollector::PtsDataCollector()
 : ptsFactory_( PtsFactory::getInstance() ),
    pts_( ptsFactory_->createPts() ),
    analyzer_( analyzer::ElasticsearchFactory::getInstance()->createIAnalyzer() ),
    chronos_( std::make_unique<::Chronos>() )
{
    projectList_.clear();
    sprintList_.clear();
    itemList_.clear();
    taskList_.clear();
    jsonObject_.clear();
}

PtsDataCollector::~PtsDataCollector()
{
    projectList_.clear();
    sprintList_.clear();
    itemList_.clear();
    taskList_.clear();
    jsonObject_.clear();

}

void PtsDataCollector::correctData()
{
    collectProjectData();
    collectSprintData();
    collectItemData();
    collectTaskData();

    this->aggrigateData();
}

void PtsDataCollector::permanentProjectData()
{
    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        auto result = project->second->createJson();
        if( result ) {
            jsonObject_.push_back( result.value() );
        }
    }

    for( auto json = begin(jsonObject_); json != end(jsonObject_); ++json )
    {
        analyzer_->registerMeasurementedData( *json );
    }
}

void PtsDataCollector::permanentSprintData()
{
    /*
    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        auto result = project->second->createJsonOfSprint();
        if( result ) {
            jsonObject_.merge( std::move(result.value()) );
        }
    }
    
    for( auto l = begin(jsonObject_); l != end(jsonObject_); ++l )
    {
        std::cout << *l << std::endl;
    }
    */
}

void PtsDataCollector::aggrigateData()
{
    for( auto sprint = begin( sprintList_ ); sprint != end( sprintList_ ); ++sprint )
    {
        sprint->second->aggrigateRemainingWorkTime( itemList_ );
    }
}

void PtsDataCollector::collectProjectData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    // 分析するためにデータの取得日時が必要
    Timestamp timestamp( chronos_->nowIso8601ExtendedGmt() );

    // PTSには、クローズした（非アクティブな）過去のプロジェクトも登録されているので、現状アクティブなプロジェクトのみを対象とする
    jsonObjectList = pts_->collectAllActiveProject();
    std::list<ProjectId> exclusiveProjects;

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        ProjectId projectId( std::stoi((*json)["projectId"] ));
        Name projectName( (*json)["projectName"] );
        ProjectId parentId( std::stoi((*json)["parentId"] ));
        exclusiveProjects.push_back( parentId );
        projectList_.insert( std::make_pair( projectId, std::make_shared<Project>( projectId, projectName, parentId, timestamp) ));
    }

    // 同じ親を持つプロジェクトが複数ある可能性があるので、重複している親プロジェクトのidを削除する
    exclusiveProjects.sort();
    exclusiveProjects.unique();

    // 親プロジェクトはSprint等を持たないので集計対象とする必要はないので削除する
    for( auto exclusive = begin( exclusiveProjects ); exclusive != end( exclusiveProjects); ++exclusive )
    {
        for( auto project = begin( projectList_ ); project != end( projectList_ ); )
        {
            if( project->first == *exclusive )
            {
                project = projectList_.erase( project );
            }
            else {
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
    for( auto project = begin( projectList_ ); project != end( projectList_ ); ++project )
    {
        jsonObjectList.merge( pts_->collectSprintInformationOf( project->first ) );
    }
    

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        ProjectId projectId( std::stoi((*json)["projectId"] ));
        SprintId sprintId( std::stoi((*json)["sprintId"]));
        Name sprintName( (*json)["sprimtName"] );
        Status status( (*json)["status"] );
        StartDate startDate( (*json)["startDate"]);
        EndDate endDate( (*json)["endDate"] );
        sprintList_.insert( std::make_pair( sprintId, std::make_shared<Sprint>( projectId, sprintId, sprintName, status, startDate, endDate )));
    }

}

void PtsDataCollector::collectItemData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    // アクティブなプロジェクトのみのSprint情報を取得するには、プロジェクトIDを指定する必要があるので
    // 取得済みのプロジェクトに対して処理を行う
    for( auto project = begin( projectList_ ); project != end( projectList_ ); ++project )
    {
        jsonObjectList.merge( pts_->collectItemInformation( project->first ) );
    }

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        ProjectId projectId( std::stoi((*json)["projectId"] ));
        SprintId sprintId( std::stoi((*json)["sprintId"]));
        ItemId itemId( std::stoi((*json)["itemId"]));
        Name itemName( (*json)["itemName"] );
        Status status( (*json)["status"] );
        StatusCode statusCode( std::stoi((*json)["statusCode"]));
        EstimatedTime totalEstimatedTime( std::stoi( (*json)["totalEstimatedTime"] ) );
        Point storyPoint(0);   // TODO 計算？
        itemList_.insert( std::make_pair( itemId, std::make_shared<Item>( itemId, itemName, projectId, sprintId, storyPoint, status, statusCode, totalEstimatedTime )));
    }

}

void PtsDataCollector::collectTaskData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    // アクティブなプロジェクトのみのSprint情報を取得するには、プロジェクトIDを指定する必要があるので
    // 取得済みのプロジェクトに対して処理を行う
    for( auto project = begin( projectList_ ); project != end( projectList_ ); ++project )
    {
        jsonObjectList.merge( pts_->collectTaskInformation( project->first ) );
    }

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        ProjectId projectId( std::stoi((*json)["projectId"] ));
        SprintId sprintId( std::stoi((*json)["sprintId"]));
        ItemId itemId( std::stoi((*json)["itemId"]));
        TaskId taskId( std::stoi((*json)["taskId"]));
        Name taskName( (*json)["taskName"] );
        Status status( (*json)["status"] );
        StatusCode statusCode( std::stoi((*json)["statusCode"]));
        Author author( (*json)["author"] );
        EstimatedTime estimatedTime( std::stoi( (*json)["estimatedTime"] ) );
        Assignee assignee( (*json)["assignee"] );
        UpdatedAt updatedAt( (*json)["updatedAt"] );
        taskList_.insert( std::make_pair( taskId, std::make_shared<Task>( projectId, sprintId, itemId, taskId, taskName, author, estimatedTime, assignee, status, statusCode, updatedAt )));
    }

}

}