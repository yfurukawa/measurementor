#include <iostream>
#include "Item.h"
#include "Task.h"

namespace measurementor
{

Item::Item( ItemId itemId, Name itemName, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status, StatusCode statusCode, EstimatedTime totalEstimatedTime )
    : itemId_(itemId),
    itemName_(itemName),
    projectId_(projectId),
    storyPoint_(storyPoint),
    status_(status),
    statusCode_(statusCode),
    sprintId_(sprintId),
    totalEstimatedTime_(totalEstimatedTime)
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
    if( this->isOpen() )
    {
        return totalEstimatedTime_;
    }
    
    return EstimatedTime(0);
}

Point Item::reportStoryPoint()
{
    if( this->isOpen() )
    {
        return storyPoint_;
    }
    
    return Point(0);
}

std::optional<std::list<std::string>> Item::createJsonOfTask( const Timestamp& timestamp )
{
    std::list<std::string> json;
    json.clear();

    if( tasks_.empty() )
    {
        return std::nullopt;
    }
    for( auto task = begin(tasks_); task != end(tasks_); ++task )
    {
        json.push_back( task->second->createJson( timestamp, projectId_, sprintId_ ) );
    }
    return json;
}

void Item::printChild()
{
    for( auto p = tasks_.begin(); p != tasks_.end(); ++p )
    {
        std::cout << p->second->id() << " : " << p->second->name() << std::endl;
    }
}

std::string Item::createJson( const Timestamp& timestamp )
{
    JsonKey tstamp("timestamp");
    jsonCreator_.holdData( tstamp, timestamp.get() );
    
    JsonKey itemId("itemId");
    jsonCreator_.holdData( itemId, itemId_.get() );

    JsonKey itemName("itemName");
    jsonCreator_.holdData( itemName, itemName_.get() );

    JsonKey projectId("projectId");
    jsonCreator_.holdData( projectId, projectId_.get() );

    JsonKey sprintId("sprintId");
    jsonCreator_.holdData( sprintId, sprintId_.get() );

    JsonKey totalEstimatedTime("totalEstimatedTime");
    jsonCreator_.holdData( totalEstimatedTime, this->reportRemainingWorkTime().get() );

    JsonKey storyPoint("storyPoint");
    jsonCreator_.holdData( storyPoint, this->reportStoryPoint().get() );

    JsonKey status("status");
    jsonCreator_.holdData( status, status_.get() );

    JsonKey statusCode("statusCode");
    jsonCreator_.holdData( statusCode, statusCode_.get() );

    return jsonCreator_.createJson();
}

bool Item::isOpen()
{
    return statusCode_ != 12;
}

}