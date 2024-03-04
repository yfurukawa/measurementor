#include "PtsDataCollector.h"
#include "../pts/openproject/OpenProjectFactory.h"   // TODO
#include "../pts/openproject/OpenProject.h"          // TODO

#include <iostream>

namespace measurementor
{

PtsDataCollector::PtsDataCollector() : ptsFactory_( PtsFactory::getInstance() )
{
    pts_ = ptsFactory_->createPts();
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
    if( pts_ != nullptr )
    delete pts_;
    pts_= nullptr;
    ptsFactory_->~PtsFactory();
}

void PtsDataCollector::correctData()
{
    collectProjectData();
    collectSprintData();
    collectItemData();
    collectTaskData();
/*
    ptsFactory_->createPts()->collectAllActiveProject( projectList_ );

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        ptsFactory_->createPts()->collectSprintInformationOf( project->second );
    }
*/
    this->aggrigateData();
}

void PtsDataCollector::permanentProjectData()
{
    jsonObject_.clear();

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        auto result = project->second->createJson();
        if( result ) {
            jsonObject_.push_back( result.value() );
        }
    }

}

void PtsDataCollector::permanentSprintData()
{
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
}

void PtsDataCollector::aggrigateData()
{
    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateStoryPointsInPBL();
    }

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateStoryPointsInProgress();
    }

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateRemainingWorkTime();
    }
}

void PtsDataCollector::collectProjectData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    jsonObjectList = pts_->collectAllActiveProject();

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        ProjectId projectId( std::stoi((*json)["projectId"] ));
        Name projectName( (*json)["projectName"] );
        ParentId parentId( std::stoi((*json)["parentId"] ));
        Timestamp timestamp("2024-03-04T12:34:56:123Z");
        projectList_.insert( std::make_pair( projectId, std::make_shared<Project>( projectId, projectName, parentId, timestamp) ));
    }
}

void PtsDataCollector::collectSprintData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    //jsonObjectList = pts_.collectSprintData();

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        //projectList_.insert( std::make_paire( ProjectId{0}, std::make_shared<Project>(ProjectId{ std::stoi(json["projectId"]) }, json["projectName"], ProjectId{ json["parentId"] }, "2024-03-04T12:34:56:123Z") ));
    }

}

void PtsDataCollector::collectItemData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    //jsonObjectList = pts_.collectItemData();

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        //projectList_.insert( std::make_paire( ProjectId{0}, std::make_shared<Project>() ));
    }

}

void PtsDataCollector::collectTaskData()
{
    std::list<std::map<std::string, std::string>> jsonObjectList;
    jsonObjectList.clear();

    //jsonObjectList = pts_.collectllTaskData();

    for( auto json = begin(jsonObjectList); json != end(jsonObjectList); ++json )
    {
        //projectList_.insert( std::make_paire( ProjectId{0}, std::make_shared<Project>() ));
    }

}

}