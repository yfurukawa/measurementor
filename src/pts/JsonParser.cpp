#include "JsonParser.h"
#include "nlohmann/json.hpp"
#include "../domain/Project.h"
#include "../domain/domainPrimitives/MeasurementPrimitives.h"
#include <iostream>

namespace pts
{

void JsonParser::collectProjectData( const std::string& jsonString, std::map<unsigned int, std::shared_ptr<measurementor::Project>>& projectList )
{
    auto j = nlohmann::json::parse( jsonString );
    
    for( int count = 0; count < j["count"]; ++count ) {
        measurementor::Id id(j["_embedded"]["elements"][count]["id"]);
        measurementor::Name name(j["_embedded"]["elements"][count]["name"]);
        projectList.insert( std::make_pair(j["_embedded"]["elements"][count]["id"], std::make_shared<measurementor::Project>(id, name) ) );
    }
}

}