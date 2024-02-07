#include "Item.h"
#include "Task.h"

namespace measurementor
{

Item::Item( Id id, Name name )
    : id_(id),
    name_(name),
    sprintId_(0),
    point_(0),
    totalEstimateTime_(0)
{
    tasks_.clear();
}

void Item::assignSprint( SprintId sprintId )
{
    sprintId_ = SprintId{ sprintId.get() };
}

void Item::addTask( Id taskId, std::unique_ptr<Task> task )
{
    tasks_.insert( std::make_pair( taskId, std::move(task) ) );
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
        totalEstimateTime_ = totalEstimateTime_ + task->second->estimateTime();
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