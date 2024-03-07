#include "Sprint.h"
#include "Item.h"
#include "Project.h"

namespace measurementor
{

Project::Project( ProjectId projectId, Name name, ProjectId parentId, Timestamp timestamp )
    : projectId_(projectId),
    name_(name),
    parentId_(parentId),
    timestamp_(timestamp),
    storyPointInprogress_(0),
    remaingStoryPoints_(0)    
{
    childProjects_.clear();
}

std::optional<std::string> Project::createJson()
{
    if( this->isParentProject() || this->isEmptyProject()  )
    {
        return std::nullopt;
    }

    JsonKey id("projectId");
    jsonCreator_.holdData( id, projectId_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );
    
    JsonKey remainingStoryPoints("remainingStoryPoints");
    jsonCreator_.holdData( remainingStoryPoints, remaingStoryPoints_.get() );

    JsonKey inProgressStoryPoints("inProgressStoryPoints");
    jsonCreator_.holdData( inProgressStoryPoints, storyPointInprogress_.get() );

    JsonKey timestamp("timestamp");
    jsonCreator_.holdData( timestamp, timestamp_.get() );

    return jsonCreator_.createJson();
}

bool Project::isParentProject() const
{
    return !(childProjects_.empty());
}

bool Project::isEmptyProject() const
{
    return childProjects_.empty();
}

}