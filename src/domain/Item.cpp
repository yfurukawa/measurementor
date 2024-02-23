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

void Item::printChild()
{
    for( auto p = tasks_.begin(); p != tasks_.end(); ++p )
    {
        std::cout << p->second->id() << " : " << p->second->name() << std::endl;
    }
}

}