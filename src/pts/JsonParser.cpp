#include <memory>
#include "JsonParser.h"
#include "nlohmann/json.hpp"
#include "../domain/Project.h"
#include "../domain/Sprint.h"
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
        project->addSprint( std::make_shared<measurementor::Sprint>( id, name ) );
    }
}

unsigned int JsonParser::pickupParentId(std::string href)
{
    auto lastPosition = href.find_last_of( "/", href.length() );
    std::string idString = href.substr( lastPosition + 1, href.length() - 1 - lastPosition);
    return std::stoi(idString);
}
}