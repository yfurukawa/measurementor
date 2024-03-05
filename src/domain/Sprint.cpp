#include "Item.h"
#include "Sprint.h"
#include "Task.h"
#include <iostream>

namespace measurementor
{

Sprint::Sprint( ProjectId projectId, SprintId sprintId, Name sprintName, Status status, StartDate startDate, EndDate endDate )
    : sprintId_(sprintId),
    sprintName_(sprintName),
    projectId_(projectId),
    totalPoint_(0),
    status_(status),
    startDate_( startDate ),
    endDate_( endDate ),
    remainingEstimatedTime_(0)
{
    items_.clear();
}

void Sprint::assignProject( ProjectId projectId )
{
    projectId_ = ProjectId{ projectId.get() };
}

void Sprint::addItem( std::shared_ptr<Item> item )
{
    items_.insert( std::make_pair( item->id(), std::move(item) ) );
}

std::optional<ProjectId> Sprint::projectId() const
{
    if( projectId_ == 0 )
    {
        return std::nullopt;
    }
    return projectId_;
}

void Sprint::aggrigateStoryPoint()
{
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        totalPoint_ = totalPoint_ + item->second->reportStoryPoint();
    }
}

void Sprint::aggrigateRemainingWorkTime()
{
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        item->second->aggrigateEstimatedTime();
    }
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        remainingEstimatedTime_ = remainingEstimatedTime_ + item->second->reportRemainingWorkTime();
    }

}

Point Sprint::reportStoryPoint()
{
    if( status_.get() == "closed" )
    {
        return Point(0);
    }
    return totalPoint_;
    
}

std::optional<std::list<std::string>> Sprint::createJsonOfItem( const Timestamp& timestamp )
{
    std::list<std::string> json;
    json.clear();

    if( items_.empty() )
    {
        return std::nullopt;
    }

    for( auto item = begin(items_); item != end(items_); ++item )
    {
        json.push_back( item->second->createJson( timestamp ) );
    }

    for( auto item = begin(items_); item != end(items_); ++item )
    {
        auto result = item->second->createJsonOfTask( timestamp );
        if( !result )
        {
            continue;
        }
        json.merge( std::move( result.value() ) );
    }

    return json;
}

void Sprint::printChild()
{
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        std::cout << item->second->id() << " : " << item->second->name() << std::endl;
    }
}

std::string Sprint::createJson( const Timestamp& timestamp )
{
    JsonKey tstamp("timestamp");
    jsonCreator_.holdData( tstamp, timestamp.get() );

    JsonKey sprintId("sprintId");
    jsonCreator_.holdData( sprintId, sprintId_.get() );

    JsonKey sprintName("name");
    jsonCreator_.holdData( sprintName, sprintName_.get() );

    JsonKey startDate("startDate");
    jsonCreator_.holdData( startDate, startDate_.get() );

    JsonKey endDate("endDate");
    jsonCreator_.holdData( endDate, endDate_.get() );

    JsonKey projectId("projectId");
    jsonCreator_.holdData( projectId, projectId_.get() );

    JsonKey totalStoryPoint("totalStoryPoint");
    jsonCreator_.holdData( totalStoryPoint, totalPoint_.get() );

    JsonKey status("status");
    jsonCreator_.holdData( status, status_.get() );

    JsonKey remainingWorkTime("remainingWorkTime");
    jsonCreator_.holdData( remainingWorkTime, remainingEstimatedTime_.get() );

    return jsonCreator_.createJson();

}

}