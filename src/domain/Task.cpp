#include "Task.h"

namespace measurementor
{

Task::Task( TaskId taskId, Name name, Author author, ItemId itemId, EstimatedTime estimatedTime, Assignee assignee, Status status, StatusCode statusCode, UpdatedAt updatedAt )
    : taskId_( taskId ),
    name_( name ),
    author_( author ),
    itemId_( itemId ),
    estimatedTime_( estimatedTime),
    assignee_( assignee ),
    status_( status ),
    statusCode_( statusCode ),
    updatedAt_( updatedAt )
{
}

EstimatedTime Task::estimatedTime()
{
    if( this->isOpen() )  // Taskがオープンのときのみ見積もり時間を返せば良い
    {
        return estimatedTime_;
    }
    
    return EstimatedTime(0);
}

std::string Task::createJson(  Timestamp timestamp, ProjectId projectId, SprintId sprintId )
{
    JsonKey tstamp("timestamp");
    jsonCreator_.holdData( tstamp, timestamp.get() );

    JsonKey pid("projectId");
    jsonCreator_.holdData( pid, projectId.get() );

    JsonKey sid("sprintId");
    jsonCreator_.holdData( sid, sprintId.get() );

    JsonKey id("taskId");
    jsonCreator_.holdData( id, taskId_.get() );

    JsonKey name("name");
    jsonCreator_.holdData( name, name_.get() );

    JsonKey author("author");
    jsonCreator_.holdData( author, author_.get() );

    JsonKey itemId("itemId");
    jsonCreator_.holdData( itemId, itemId_.get() );

    JsonKey estimatedTime("estimatedTime");
    jsonCreator_.holdData( estimatedTime, estimatedTime_.get() );

    JsonKey assignee("assignee");
    jsonCreator_.holdData( assignee, assignee_.get() );

    JsonKey status("status");
    jsonCreator_.holdData( status, status_.get() );

    JsonKey statusCode("statusCode");
    jsonCreator_.holdData( statusCode, statusCode_.get() );

    JsonKey updatedAt("updatedAt");
    jsonCreator_.holdData( updatedAt, updatedAt_.get() );
    
    return jsonCreator_.createJson();
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

bool Task::isOpen()
{
    return statusCode_ != 12;
}
}