#include "Task.h"

namespace measurementor
{

Task::Task( Id id, Name name, Author author, ItemId itemId )
    : id_( id ),
    name_( name ),
    author_( author ),
    itemId_( itemId ),
    estimateTime_(0),
    assignee_(""),
    status_(1)
{
}

void Task::updateStatus( unsigned int newStatus )
{
    if( status_ > newStatus )
    {
        // TODO 手戻りなのでその処理を作る
        return;
    }
    
    status_ = newStatus;
}

}