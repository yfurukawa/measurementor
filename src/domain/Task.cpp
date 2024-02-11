#include "Task.h"

namespace measurementor
{

Task::Task( Id id, Name name, Author author, ItemId itemId, EstimateTime estimateTime, Assignee assignee, Status status, StatusCode statusCode, UpdatedAt updatedAt )
    : id_( id ),
    name_( name ),
    author_( author ),
    itemId_( itemId ),
    estimateTime_( estimateTime),
    assignee_( assignee ),
    status_( status ),
    statusCode_( statusCode ),
    updatedAt_( updatedAt )
{
}

void Task::updateStatus( unsigned int newStatus )
{
    /*
    if( status_ > newStatus )
    {
        // TODO 手戻りなのでその処理を作る
        return;
    }
    
    //status_ = newStatus;
    */
}

}