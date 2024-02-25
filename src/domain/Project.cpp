#include "Sprint.h"
#include "Item.h"
#include "Project.h"

namespace measurementor
{

Project::Project( Id id, Name name, ParentId parentId )
    : id_(id),
    name_(name),
    parentId_(parentId),
    storyPointInprogress_(0),
    remaingStoryPoints_(0)    
{
    childProjects_.clear();
    sprints_.clear();
    productBackLog_.clear();
}

void Project::relateChildProject( Id childProjectId )
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

std::string Project::createJson()
{
    JsonKey id("id");
    jsonCreator_.holdData( id, id_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );
    
    JsonKey remainingStoryPoints("remainingStoryPoints");
    jsonCreator_.holdData( remainingStoryPoints, remaingStoryPoints_.get() );

    JsonKey inProgressStoryPoints("inProgressStoryPoints");
    jsonCreator_.holdData( inProgressStoryPoints, storyPointInprogress_.get() );

    return jsonCreator_.createJson();
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
    measurementor::Id id{ sprintId.get() };
    return sprints_.at( id );
}

}