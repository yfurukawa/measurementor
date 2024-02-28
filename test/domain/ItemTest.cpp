#include <memory>
#include <string>
#include "ItemTest.h"
#include "../../src/domain/Item.h"
#include "../../src/domain/Task.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

namespace measurementor
{
    void ItemTest::SetUp()
    {
    }

    void ItemTest::TearDown()
    {
        delete sut;
    }

    TEST_F(ItemTest, createJson_noAssignedTask)
    {
        ItemId id(1);
        Name name("Test Item");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        std::string expected(R"({"itemId":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"timestamp":"2024-02-28T12:34:56.123","totalEstimatedTime":0.0})");

        EXPECT_EQ( expected, sut->createJson( tstamp ) );
 
    }

    TEST_F(ItemTest, createJson_OneTask)
    {
        // Task
        TaskId taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Item
        ItemId id(1);
        Name name("Test Item");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"itemId":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"timestamp":"2024-02-28T12:34:56.123","totalEstimatedTime":5.5})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson( tstamp ) );
    }

    TEST_F(ItemTest, createJson_reportPoint_ItemStilOpen)
    {
        // Task
        TaskId taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Item
        ItemId id(1);
        Name name("Test Item");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"itemId":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"timestamp":"2024-02-28T12:34:56.123","totalEstimatedTime":5.5})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson( tstamp ) );
 
    }

    TEST_F(ItemTest, createJson_reportPoint_ItemWasClosed)
    {
        // Task
        TaskId taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode taskStatusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, taskStatusCode, updatedAt );

        // Item
        ItemId id(1);
        Name name("Test Item");
        const Timestamp tstamp("2024-02-28T12:34:56.123");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("Closed");
        StatusCode statusCode(12);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"itemId":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"Closed","statusCode":12,"storyPoint":0,"timestamp":"2024-02-28T12:34:56.123","totalEstimatedTime":0.0})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson( tstamp ) );
 
    }
}