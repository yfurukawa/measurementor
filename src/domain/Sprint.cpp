#include "Item.h"
#include "Sprint.h"
#include "Task.h"
#include <iostream>

namespace measurementor
{

Sprint::Sprint( Id id, Name name, StartDate startDate, EndDate endDate )
    : id_(id),
    name_(name),
    projectId_(0),
    totalPoint_(0),
    status_(""),
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
        totalPoint_ = totalPoint_ + item->second->point();
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


void Sprint::printChild()
{
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        std::cout << item->second->id() << " : " << item->second->name() << std::endl;
    }
}

std::string Sprint::createJson()
{
    
    if( !items_.empty() )
    {
        this->aggrigateRemainingWorkTime();
        JsonKey keyItem("item");

        for( auto item = begin(items_); item != end(items_); ++item )
        {
            JsonObject object( item->second->createJson() );
            jsonCreator_.holdDataAsArray(keyItem, object);
        }
    }

    JsonKey id("id");
    jsonCreator_.holdData( id, id_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );

    JsonKey startDate("startDate");
    jsonCreator_.holdData( startDate, startDate_.get() );

    JsonKey endDate("endDate");
    jsonCreator_.holdData( endDate, endDate_.get() );

    JsonKey projectId("projectId");
    jsonCreator_.holdData( projectId, projectId_.get() );

    JsonKey totalStoryPoint("totalStoryPoint");
    jsonCreator_.holdData( totalStoryPoint, totalPoint_.get() );

    JsonKey status("status");
    jsonCreator_.holdData( status, status_ );

    JsonKey remainingWorkTime("remainingWorkTime");
    jsonCreator_.holdData( remainingWorkTime, remainingEstimatedTime_.get() );

    return jsonCreator_.createJson();

}

}