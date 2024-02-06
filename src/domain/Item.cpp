#include "Item.h"

namespace measurementor
{

Item::Item( Id id, Name name )
    : id_(id),
    name_(name),
    versionId_(0),
    point_(0),
    totalEstimateTime_(0)
{
    tasks_.clear();
}

void Item::assignVersion( VersionId versionId )
{
    versionId_ = VersionId{ versionId.get() };
}

void Item::addTask( Id taskId )
{
    tasks_.emplace_back( taskId );
}

std::optional<VersionId> Item::versionId() const
{
    if( versionId_ == 0 )
    {
        return std::nullopt;
    }
    return versionId_;
}

void Item::calculateTotalEstimateTime()
{
    for( auto task : tasks_ )
    {
        
    }
}

}