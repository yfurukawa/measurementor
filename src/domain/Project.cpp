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
    sprints_.clear();
    productBackLog_.clear();
}

void Project::relateChildProject( ProjectId childProjectId )
{
    childProjects_.emplace_back( childProjectId );
}

void Project::addSprint( std::shared_ptr<Sprint> sprint )
{
    sprints_.insert( std::make_pair( sprint->id(), std::move( sprint ) ) );
}

void Project::addPBL( std::shared_ptr<Item> pbi )
{
    productBackLog_.insert( std::make_pair( pbi->id(), std::move( pbi ) ) );
}

void Project::aggrigateStoryPointsInPBL()
{
    for( auto pbi = begin(productBackLog_); pbi != end(productBackLog_); ++pbi )
    {
        remaingStoryPoints_ = remaingStoryPoints_ + pbi->second->reportStoryPoint();
    }
}

void Project::aggrigateStoryPointsInProgress()
{
    for( auto sprint = begin(sprints_); sprint != end(sprints_); ++sprint )
    {
        sprint->second->aggrigateStoryPoint();
        storyPointInprogress_ = storyPointInprogress_ + sprint->second->reportStoryPoint();
    }
}

void Project::aggrigateRemainingWorkTime()
{
    for( auto sprint = begin(sprints_); sprint != end(sprints_); ++sprint )
    {
        sprint->second->aggrigateRemainingWorkTime();
    }
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

std::optional<std::list<std::string>> Project::createJsonOfSprint()
{
    if( this->isParentProject() || this->isEmptyProject()  )
    {
        return std::nullopt;
    }

    std::list<std::string> JsonObject4Sprint;
    JsonObject4Sprint.clear();

    for( auto sprint = begin(sprints_); sprint != end(sprints_); ++sprint )
    {
        JsonObject4Sprint.push_back( sprint->second->createJson( timestamp_ ) );
    }

    for( auto sprint = begin(sprints_); sprint != end(sprints_); ++sprint )
    {
        auto result = sprint->second->createJsonOfItem( timestamp_ );
        if( !result )
        {
            continue;;
        }
        JsonObject4Sprint.merge( std::move(result.value()) );
    }
    return JsonObject4Sprint;
}

void Project::printChild()
{
    for( auto p = childProjects_.begin(); p != childProjects_.end(); ++p )
    {
        std::cout << "   " << *p << std::endl;
    }
    for( auto s = begin(sprints_); s != end(sprints_); ++s )
    {
        std::cout << "   " << s->second->id() << " : " << s->second->name() << std::endl;
    }
}

std::shared_ptr<Sprint> Project::getSprint( measurementor::SprintId sprintId )
{
    measurementor::SprintId id{ sprintId.get() };
    return sprints_.at( id );
}

bool Project::isParentProject() const
{
    return !(childProjects_.empty()) && (sprints_.empty()) && (productBackLog_.empty()) ;
}

bool Project::isEmptyProject() const
{
    return childProjects_.empty() && sprints_.empty() && productBackLog_.empty();
}

}