#include <map>
#include <memory>
#include <string>
#include "JsonParser.h"
#include "nlohmann/json.hpp"
#include "../domain/Project.h"
#include "../domain/Sprint.h"
#include "../domain/Item.h"
#include "../domain/Task.h"

#include "../domain/domainPrimitives/MeasurementPrimitives.h"
#include <iostream>

namespace pts
{

void JsonParser::collectProjectData( const std::string& jsonString, std::map<unsigned int, std::shared_ptr<measurementor::Project>>& projectList )
{
    auto j = nlohmann::json::parse( jsonString );
    
    // プロジェクトリストを作る際に、子プロジェクトを別のリストに隔離しておき
    // 次に子プロジェクトのリストを探索し、親プロジェクト内の小プロジェクトリストに追加する
    for( int count = 0; count < j["count"]; ++count ) {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        measurementor::ParentId parentId( (j["_embedded"]["elements"][count]["_links"]["parent"]["href"]).is_null() ? 0 : pickupParentId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]) );
        projectList.insert( std::make_pair(j["_embedded"]["elements"][count]["id"], std::make_shared<measurementor::Project>(id, name, parentId) ) );
    }

    for( auto project = std::begin(projectList); project != std::end(projectList); ++project )
    {
        if( project->second->parentId() != 0 )
        {
            projectList.at(project->second->parentId().get())->relateChildProject(project->second->id());
        }
    }

}

void JsonParser::collectSprintData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project )
{
    auto j = nlohmann::json::parse( jsonString );

    for( int count = 0; count < j["count"]; ++count )
    {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        measurementor::StartDate startDate( (j["_embedded"]["elements"][count]["startDate"]).is_null() ? "" : j["_embedded"]["elements"][count]["startDate"] );
        measurementor::EndDate endDate( (j["_embedded"]["elements"][count]["endDate"]).is_null() ? "" : j["_embedded"]["elements"][count]["endDate"] );
        project->addSprint( std::make_shared<measurementor::Sprint>( id, name, startDate, endDate ) );
    }
}

void JsonParser::collectPBLandTaskData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project )
{
    auto j = nlohmann::json::parse( jsonString );
    std::map<measurementor::Id, std::shared_ptr<measurementor::Item>> items{};
    std::map<measurementor::Id, std::shared_ptr<measurementor::Task>> tasks{};

    std::string type("");

    for( int count = 0; count < j["count"]; ++count )
    {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["subject"]);
        
        type = j["_embedded"]["elements"][count]["_lynks"]["type"]["title"];
        if( type == "Feature") {
            measurementor::ProjectId projectId( pickupParentId( j["_embedded"]["elements"][count]["_lynks"]["Project"]["href"] ) );
            measurementor::SprintId sprintId( (j["_embedded"]["elements"][count]["_lynks"]["version"]["href"]).is_null() ? 0 : (pickupParentId(j["_embedded"]["elements"][count]["_lynks"]["version"]["href"])) );
            measurementor::Point storyPoint( (j["_embedded"]["elements"][count]["storyPoints"])); //.is_null() ? 0 : j["_embedded"]["elements"][count]["storyPoints"] );
            measurementor::Status status( j["_embedded"]["elements"][count]["_lynks"]["status"]["title"] );
            items.insert( std::make_pair( id, std::make_shared<measurementor::Item>(id, name, projectId, sprintId, storyPoint, status) ) );
        }
        else if( type == "Task" )
        {
            measurementor::ItemId itemId( pickupParentId(j["_embedded"]["elements"][count]["_lynks"]["parent"]) );
            measurementor::Author author( j["_embedded"]["elements"][count]["_lynks"]["author"]["title"] );
            measurementor::EstimateTime estimateTime( j["_embedded"]["elements"][count]["estimatedTime"]);
            measurementor::Assignee assignee( (j["_embedded"]["elements"][count]["_lynks"]["assignee"]["href"]).is_null() ? "" : j["_embedded"]["elements"][count]["_lynks"]["assignee"]["title"] );
            measurementor::Status status( j["_embedded"]["elements"][count]["_lynks"]["status"]["title"] );
            measurementor::StatusCode statusCode( pickupParentId(j["_embedded"]["elements"][count]["_lynks"]["status"]["title"] ) );
            measurementor::UpdatedAt updatedAt( j["_embedded"]["elements"][count]["updatedAt"]);
            tasks.insert( std::make_pair( id, std::make_shared<measurementor::Task>(id, name, author, itemId, estimateTime, assignee, status, statusCode, updatedAt ) ) );
        }   
    }

    for( auto task = begin(tasks); task != end(tasks); ++task )
    {
        items.at(task->second->itemId())->addTask( task->second );
    }

    for( auto item = begin(items); item != end(items); ++item )
    {
        auto result = item->second->sprintId();
        if( result )
        {
            project->getSprint( result.value() )->addItem( item->second );
        }
        else
        {
            project->addPBL( item->second );
        }
    }
}

unsigned int JsonParser::pickupParentId(std::string href)
{
    auto lastPosition = href.find_last_of( "/", href.length() );
    std::string idString = href.substr( lastPosition + 1, href.length() - 1 - lastPosition);
    return std::stoi(idString);
}
}