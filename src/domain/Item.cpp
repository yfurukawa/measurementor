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
}

Point Item::reportStoryPoint(SprintId sprintId)
{
    if( this->isOpen() && sprintId_ == sprintId )
    {
        return storyPoint_;
    }

    return Point(0);
}

EstimatedTime Item::reportRemainingWorkTime(SprintId sprintId)
{
    if( this->isOpen() && sprintId_ == sprintId )
    {
        return totalEstimatedTime_;
    }
    
    return EstimatedTime(0);
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
    jsonCreator_.holdData( totalEstimatedTime, totalEstimatedTime_.get() );

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

Point Item::reportStoryPoint()
{
    if( this->isOpen() )
    {
        return storyPoint_;
    }
    
    return Point(0);
}

}