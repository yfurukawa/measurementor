#include <memory>
#include <string>
#include "SprintTest.h"
#include "../../src/domain/Item.h"
#include "../../src/domain/Sprint.h"
#include "../../src/domain/Task.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

namespace measurementor
{
    void SprintTest::SetUp()
    {
    }

    void SprintTest::TearDown()
    {
        delete sut;
    }

    TEST_F(SprintTest, createJson_noAssignedItem)
    {
        Id id(1);
        Name name("Test Sprint");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        ProjectId projectId(10);
        Status status("open");
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
         
        sut = new Sprint( id, name, status, startDate, endDate );

        std::string expected(R"({"endDate":"2024-02-25T12:34:56+09:00","name":"Test Sprint","projectId":0,"remainingWorkTime":0.0,"sprintId":1,"startDate":"2024-02-23T12:34:56+09:00","status":"open","timestamp":"2024-02-28T12:34:56.123","totalStoryPoint":0})");

        sut->aggrigateRemainingWorkTime();
        sut->aggrigateStoryPoint();
        EXPECT_EQ( expected, sut->createJson( tstamp ) );
 
    }

    TEST_F(SprintTest, createJson_OneItemAndTask)
    {
        // Task
        Id taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Id itemId(1); Declare in Task
        Name itemName("Test Item");
        ProjectId itemProjectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status itemStatus("open");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, sprintId, storyPoint, itemStatus, statusCode );

        item->addTask( task );

        // Sprint
        Id id(1);
        Name name("Test Sprint");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        Status status("open");
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
        sut = new Sprint( id, name, status, startDate, endDate );        

        sut->addItem( item );

        std::string expected(R"({"endDate":"2024-02-25T12:34:56+09:00","name":"Test Sprint","projectId":0,"remainingWorkTime":5.5,"sprintId":1,"startDate":"2024-02-23T12:34:56+09:00","status":"open","timestamp":"2024-02-28T12:34:56.123","totalStoryPoint":3})");

        sut->aggrigateRemainingWorkTime();
        sut->aggrigateStoryPoint();
        EXPECT_EQ( expected, sut->createJson( tstamp ) );
    }

    TEST_F(SprintTest, reportStoryPoint_SprintStillOpen)
    {
        // Task
        Id taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Id itemId(1); Declare in Task
        Name itemName("Test Item");
        ProjectId itemProjectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status itemStatus("open");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, sprintId, storyPoint, itemStatus, statusCode );

        item->addTask( task );

        // Sprint
        Id id(1);
        Name name("Test Sprint");
        Status status("open");
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
        sut = new Sprint( id, name, status, startDate, endDate );        
        sut->addItem( item );
        double expected(3.0);

        sut->aggrigateStoryPoint();
        EXPECT_EQ( expected, sut->reportStoryPoint().get() );
    }

    TEST_F(SprintTest, reportStoryPoint_SprintWasClosed)
    {
        // Task
        Id taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Id itemId(1); Declare in Task
        Name itemName("Test Item");
        ProjectId itemProjectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status itemStatus("open");
        StatusCode statusCode(11);
        SprintId sprintId(12);
 
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, sprintId, storyPoint, itemStatus, statusCode );

        item->addTask( task );

        // Sprint
        Id id(1);
        Name name("Test Sprint");
        Status status("closed");
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
        sut = new Sprint( id, name, status, startDate, endDate );        
        sut->addItem( item );
        double expected(0.0);

        sut->aggrigateStoryPoint();
        EXPECT_EQ( expected, sut->reportStoryPoint().get() );
    }
}