#include "JsonParser.h"
#include "nlohmann/json.hpp"
#include "../domain/Project.h"
#include "../domain/domainPrimitives/MeasurementPrimitives.h"
#include <iostream>

namespace pts
{

void JsonParser::collectProjectData( const std::string& jsonString, std::map<unsigned int, std::shared_ptr<measurementor::Project>>& projectList )
{
    std::map<unsigned int, std::shared_ptr<measurementor::Project>> child;
    child.clear();

    auto j = nlohmann::json::parse( jsonString );
    
    for( int count = 0; count < j["count"]; ++count ) {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        //std::string href(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]);

        if( j["_embedded"]["elements"][count]["_links"]["parent"]["href"] != nullptr )
        {
            child.insert( std::make_pair( pickupParentId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]), std::make_shared<measurementor::Project>(id, name) ) );
        }
        else
        {
            projectList.insert( std::make_pair(j["_embedded"]["elements"][count]["id"], std::make_shared<measurementor::Project>(id, name) ) );
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