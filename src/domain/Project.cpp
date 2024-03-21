#include "Sprint.h"
#include "Item.h"
#include "Project.h"

namespace measurementor
{

Project::Project( ProjectId projectId, Name projectName, ProjectId parentId, Timestamp timestamp )
    : projectId_(projectId),
    name_(projectName),
    parentId_(parentId),
    timestamp_(timestamp),
    remaingStoryPoints_(0)    
{
}

std::string Project::createJson()
{
    JsonKey indexType("indexType");
    std::string type("Project");
    jsonCreator_.holdData( indexType, type );

    JsonKey id("projectId");
    jsonCreator_.holdData( id, projectId_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );
    
    JsonKey remainingStoryPoints("remainingStoryPoints");
    jsonCreator_.holdData( remainingStoryPoints, remaingStoryPoints_.get() );

    JsonKey timestamp("timestamp");
    jsonCreator_.holdData( timestamp, timestamp_.get() );

    return jsonCreator_.createJson();
}

void Project::registerStoryPoint(Point remainingStoryPint)
{
    remaingStoryPoints_ = remainingStoryPint;
}

}