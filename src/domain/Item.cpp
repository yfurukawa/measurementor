#include <iostream>
#include "Item.h"
#include "Task.h"

namespace measurementor
{

Item::Item( Id id, Name name, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status )
    : id_(id),
    name_(name),
    projectId_(projectId),
    storyPoint_(storyPoint),
    status_(status),
    sprintId_(sprintId),
    totalEstimatedTime_(0)
{
    tasks_.clear();
}

void Item::assignSprint( SprintId sprintId )
{
    sprintId_ = SprintId{ sprintId.get() };
}

void Item::addTask( std::shared_ptr<Task> task )
{
    tasks_.insert( std::make_pair( task->id(), std::move(task) ) );
}

std::optional<SprintId> Item::sprintId() const
{
    if( sprintId_ == 0 )
    {
        return std::nullopt;
    }
    return sprintId_;
}

void Item::aggrigateEstimatedTime()
{
    for( auto task = begin(tasks_); task != end(tasks_); ++task )
    {
        totalEstimatedTime_ = totalEstimatedTime_ + task->second->estimatedTime();
    }
}

EstimatedTime Item::reportRemainingWorkTime()
{
    return totalEstimatedTime_;
}

void Item::printChild()
{
    for( auto p = tasks_.begin(); p != tasks_.end(); ++p )
    {
        std::cout << p->second->id() << " : " << p->second->name() << std::endl;
    }
}

std::string Item::createJson()
{
    if( !tasks_.empty() )
    {
        this->aggrigateEstimatedTime();
        JsonKey keyTask("task");

        for( auto task = begin(tasks_); task != end(tasks_); ++task )
        {
            JsonObject object( task->second->createJson() );
            jsonCreator_.holdDataAsArray(keyTask, object);
        }
    }

    JsonKey id("id");
    jsonCreator_.holdData( id, id_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );

    JsonKey projectId("projectId");
    jsonCreator_.holdData( projectId, projectId_.get() );

    JsonKey sprintId("sprintId");
    jsonCreator_.holdData( sprintId, sprintId_.get() );

    JsonKey totalEstimatedTime("totalEstimatedTime");
    jsonCreator_.holdData( totalEstimatedTime, totalEstimatedTime_.get() );

    JsonKey storyPoint("storyPoint");
    jsonCreator_.holdData( storyPoint, storyPoint_.get() );

    JsonKey status("status");
    jsonCreator_.holdData( status, status_.get() );

    return jsonCreator_.createJson();
}

}