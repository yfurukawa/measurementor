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
        measurementor::ProjectId id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        measurementor::ParentId parentId( (j["_embedded"]["elements"][count]["_links"]["parent"]["href"]).is_null() ? 0 : pickupId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]) );
        measurementor::Timestamp timestamp(chronos_.nowIso8601ExtendedGmt());
        projectList.insert( std::make_pair(j["_embedded"]["elements"][count]["id"], std::make_shared<measurementor::Project>(id, name, parentId, timestamp) ) );
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
        measurementor::SprintId id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        measurementor::Status status(j["_embedded"]["elements"][count]["status"]);
        measurementor::StartDate startDate( (j["_embedded"]["elements"][count]["startDate"]).is_null() ? "" : j["_embedded"]["elements"][count]["startDate"] );
        measurementor::EndDate endDate( (j["_embedded"]["elements"][count]["endDate"]).is_null() ? "" : j["_embedded"]["elements"][count]["endDate"] );
        project->addSprint( std::make_shared<measurementor::Sprint>( id, name, status, startDate, endDate ) );
    }
}

void JsonParser::collectPBLandTaskData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project )
{
    auto j = nlohmann::json::parse( jsonString );
    std::map<measurementor::ItemId, std::shared_ptr<measurementor::Item>> items{};
    std::map<measurementor::TaskId, std::shared_ptr<measurementor::Task>> tasks{};

    std::string type("");

    for( int count = 0; count < j["count"]; ++count )
    {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        
        type = j["_embedded"]["elements"][count]["_links"]["type"]["title"];
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

std::list<std::map<std::string, std::string>> JsonParser::collectItemData( const std::string& jsonString )
{
    std::list<std::map<std::string, std::string>> itemList;
    std::map<std::string, std::string> parsedData;
    itemList.clear();
    auto j = nlohmann::json::parse( jsonString );
    std::string type("");

    for( int count = 0; count < j["count"]; ++count )
    {
        parsedData.clear();
        type = j["_embedded"]["elements"][count]["_links"]["type"]["title"];

        if( type == "Feature" )
        {
            unsigned int itemId(j["_embedded"]["elements"][count]["id"]);
            parsedData.insert( std::make_pair( "itemId", std::to_string( itemId ) ));
            parsedData.insert( std::make_pair( "itemName", j["_embedded"]["elements"][count]["subject"]) );
            parsedData.insert( std::make_pair( "projectId", std::to_string( pickupId(j["_embedded"]["elements"][count]["_links"]["project"]["href"]) ) ));
            if( (j["_embedded"]["elements"][count]["_links"]["version"]["href"]).is_null() )
            {
                // プロダクトバックログに積まれているPBIはスプリントに紐付いていないのでsprintIdは0にする
                parsedData.insert( std::make_pair( "sprintId", "0" ) );
            }
            else
            {
                parsedData.insert( std::make_pair( "sprintId", std::to_string( pickupId(j["_embedded"]["elements"][count]["_links"]["version"]["href"])) ));
            }
            parsedData.insert( std::make_pair( "storyPoint", std::to_string((int)j["_embedded"]["elements"][count]["storyPoints"])) );
            parsedData.insert( std::make_pair( "status", j["_embedded"]["elements"][count]["_links"]["status"]["title"] ));
            parsedData.insert( std::make_pair( "statusCode", std::to_string( pickupId(j["_embedded"]["elements"][count]["_links"]["status"]["href"]) )));
            itemList.push_back( parsedData );
        }
        
    }

    return itemList;
}

std::list<std::map<std::string, std::string>> JsonParser::collectTaskData( const std::string& jsonString )
{
    std::list<std::map<std::string, std::string>> taskList;
    std::map<std::string, std::string> parsedData;
    taskList.clear();
    auto j = nlohmann::json::parse( jsonString );
    std::string type("");

    for( int count = 0; count < j["count"]; ++count )
    {
        parsedData.clear();
        type = j["_embedded"]["elements"][count]["_links"]["type"]["title"];

        if( type == "Task" )
        {
        
            unsigned int taskId(j["_embedded"]["elements"][count]["id"]);
            parsedData.insert( std::make_pair( "taskId", std::to_string( taskId ) ) );
            parsedData.insert( std::make_pair( "taskName", j["_embedded"]["elements"][count]["subject"] ));

            parsedData.insert( std::make_pair( "itemId", std::to_string(pickupId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]) ) ));
            parsedData.insert( std::make_pair( "sprintId", std::to_string(pickupId(j["_embedded"]["elements"][count]["_links"]["version"]["href"]) ) ));
            parsedData.insert( std::make_pair( "projectId", std::to_string(pickupId(j["_embedded"]["elements"][count]["_links"]["project"]["href"]) ) ));
            parsedData.insert( std::make_pair( "author", j["_embedded"]["elements"][count]["_links"]["author"]["title"] ));
            // 見積もり時間はOpenProjectの設定により取得先を変更する必要がありそう
            if( (j["_embedded"]["elements"][count]["remainingTime"]).is_null() )
            {
                parsedData.insert( std::make_pair( "estimatedTime", "0" ));    
            }
            else
            {
                parsedData.insert( std::make_pair( "estimatedTime", pickupHour( j["_embedded"]["elements"][count]["remainingTime"] )));
            }
            parsedData.insert( std::make_pair( "assignee", (j["_embedded"]["elements"][count]["_links"]["assignee"]["href"]).is_null() ? "" : j["_embedded"]["elements"][count]["_links"]["assignee"]["title"] ) );
            parsedData.insert( std::make_pair( "status", j["_embedded"]["elements"][count]["_links"]["status"]["title"] ));
            parsedData.insert( std::make_pair( "statusCode", std::to_string( pickupId(j["_embedded"]["elements"][count]["_links"]["status"]["href"] ) )));
            parsedData.insert( std::make_pair( "updatedAt", j["_embedded"]["elements"][count]["updatedAt"]) );

            taskList.push_back( parsedData );
        }
    }
    return taskList;
}

unsigned int JsonParser::pickupId(std::string href)
{
    auto lastPosition = href.find_last_of( "/", href.length() );
    std::string idString = href.substr( lastPosition + 1, href.length() - 1 - lastPosition);
    return std::stoi(idString);
}

// TODO delete
std::shared_ptr<measurementor::Item> JsonParser::extractPBLData( nlohmann::json jsonString, int count )
{
    measurementor::ItemId id(jsonString["_embedded"]["elements"][count]["id"]);
    measurementor::Name name(jsonString["_embedded"]["elements"][count]["subject"]);
    measurementor::ProjectId projectId( pickupId( jsonString["_embedded"]["elements"][count]["_links"]["Project"]["href"] ) );
    measurementor::SprintId sprintId( (jsonString["_embedded"]["elements"][count]["_links"]["version"]["href"]).is_null() ? 0 : (pickupId(jsonString["_embedded"]["elements"][count]["_links"]["version"]["href"])) );
    measurementor::Point storyPoint( (jsonString["_embedded"]["elements"][count]["storyPoints"]));
    measurementor::Status status( jsonString["_embedded"]["elements"][count]["_links"]["status"]["title"] );
    measurementor::StatusCode statusCode( pickupId(jsonString["_embedded"]["elements"][count]["_links"]["status"]["href"]) );
    return std::make_shared<measurementor::Item>(id, name, projectId, sprintId, storyPoint, status, statusCode);
}

// TODO delete
std::shared_ptr<measurementor::Task> JsonParser::extractTaskData( nlohmann::json jsonString, int count )
{
    measurementor::TaskId id(jsonString["_embedded"]["elements"][count]["id"]);
    measurementor::Name name(jsonString["_embedded"]["elements"][count]["subject"]);
    measurementor::ItemId itemId( pickupId(jsonString["_embedded"]["elements"][count]["_links"]["parent"]) );
    measurementor::Author author( jsonString["_embedded"]["elements"][count]["_links"]["author"]["title"] );
    measurementor::EstimatedTime estimatedTime( jsonString["_embedded"]["elements"][count]["estimatedTime"]);
    measurementor::Assignee assignee( (jsonString["_embedded"]["elements"][count]["_links"]["assignee"]["href"]).is_null() ? "" : jsonString["_embedded"]["elements"][count]["_links"]["assignee"]["title"] );
    measurementor::Status status( jsonString["_embedded"]["elements"][count]["_links"]["status"]["title"] );
    measurementor::StatusCode statusCode( pickupId(jsonString["_embedded"]["elements"][count]["_links"]["status"]["href"] ) );
    measurementor::UpdatedAt updatedAt( jsonString["_embedded"]["elements"][count]["updatedAt"]);
    return std::make_shared<measurementor::Task>(id, name, author, itemId, estimatedTime, assignee, status, statusCode, updatedAt );
}

std::string JsonParser::pickupHour( std::string remainingTimeValue )
{
    int length( remainingTimeValue.length() );
    return remainingTimeValue.substr(2, length - 3 );
}

}