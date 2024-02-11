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
    endDate_( endDate )
{
    items_.clear();
}

void Sprint::assignProject( ProjectId projectId )
{
    projectId_ = ProjectId{ projectId.get() };
}

void Sprint::addItem( Id itemId, std::unique_ptr<Item> item )
{
    items_.insert( std::make_pair(itemId, std::move(item) ) );
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

void Sprint::printChild()
{
    for( auto item = begin(items_); item != end(items_); ++item )
    {
        std::cout << item->second->id() << " : " << item->second->name() << std::endl;
    }
}

}