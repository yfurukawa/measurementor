#include <map>
#include <memory>
#include <string>
#include "JsonParser.h"
#include "../../domain/Project.h"
#include "../../domain/Sprint.h"
#include "../../domain/Item.h"
#include "../../domain/Task.h"

#include "../../domain/domainPrimitives/MeasurementPrimitives.h"
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
        measurementor::ParentId parentId( (j["_embedded"]["elements"][count]["_links"]["parent"]["href"]).is_null() ? 0 : pickupId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]) );
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
        
        type = j["_embedded"]["elements"][count]["_lynks"]["type"]["title"];
        if( type == "Feature") {
            items.insert( std::make_pair( id, extractPBLData( j, count ) ) );
        }
        else if( type == "Task" )
        {
            tasks.insert( std::make_pair( id, extractTaskData( j, count ) ) );
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

unsigned int JsonParser::pickupId(std::string href)
{
    auto lastPosition = href.find_last_of( "/", href.length() );
    std::string idString = href.substr( lastPosition + 1, href.length() - 1 - lastPosition);
    return std::stoi(idString);
}

std::shared_ptr<measurementor::Item> JsonParser::extractPBLData( nlohmann::json jsonString, int count )
{
    measurementor::Id id(jsonString["_embedded"]["elements"][count]["id"]);
    measurementor::Name name(jsonString["_embedded"]["elements"][count]["subject"]);
    measurementor::ProjectId projectId( pickupId( jsonString["_embedded"]["elements"][count]["_lynks"]["Project"]["href"] ) );
    measurementor::SprintId sprintId( (jsonString["_embedded"]["elements"][count]["_lynks"]["version"]["href"]).is_null() ? 0 : (pickupId(jsonString["_embedded"]["elements"][count]["_lynks"]["version"]["href"])) );
    measurementor::Point storyPoint( (jsonString["_embedded"]["elements"][count]["storyPoints"]));
    measurementor::Status status( jsonString["_embedded"]["elements"][count]["_lynks"]["status"]["title"] );
    return std::make_shared<measurementor::Item>(id, name, projectId, sprintId, storyPoint, status);
}

std::shared_ptr<measurementor::Task> JsonParser::extractTaskData( nlohmann::json jsonString, int count )
{
    measurementor::Id id(jsonString["_embedded"]["elements"][count]["id"]);
    measurementor::Name name(jsonString["_embedded"]["elements"][count]["subject"]);
    measurementor::ItemId itemId( pickupId(jsonString["_embedded"]["elements"][count]["_lynks"]["parent"]) );
    measurementor::Author author( jsonString["_embedded"]["elements"][count]["_lynks"]["author"]["title"] );
    measurementor::EstimatedTime estimatedTime( jsonString["_embedded"]["elements"][count]["estimatedTime"]);
    measurementor::Assignee assignee( (jsonString["_embedded"]["elements"][count]["_lynks"]["assignee"]["href"]).is_null() ? "" : jsonString["_embedded"]["elements"][count]["_lynks"]["assignee"]["title"] );
    measurementor::Status status( jsonString["_embedded"]["elements"][count]["_lynks"]["status"]["title"] );
    measurementor::StatusCode statusCode( pickupId(jsonString["_embedded"]["elements"][count]["_lynks"]["status"]["title"] ) );
    measurementor::UpdatedAt updatedAt( jsonString["_embedded"]["elements"][count]["updatedAt"]);
    return std::make_shared<measurementor::Task>(id, name, author, itemId, estimatedTime, assignee, status, statusCode, updatedAt );
}

}