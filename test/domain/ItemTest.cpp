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
        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"totalEstimatedTime":0.0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }

    TEST_F(ItemTest, createJson_OneTask)
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

        // Item
        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":5.5})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson() );
    }

    TEST_F(ItemTest, createJson_reportPoint_ItemStilOpen)
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

        // Item
        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("New");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"New","statusCode":1,"storyPoint":3,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":5.5})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson() );
 
    }

    TEST_F(ItemTest, createJson_reportPoint_ItemWasClosed)
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

        // Item
        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("Closed");
        StatusCode statusCode(12);
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status, statusCode );

        sut->addTask( task );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"Closed","statusCode":12,"storyPoint":0,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":0.0})");
        sut->aggrigateEstimatedTime();  // 通常はSprintから呼び出されるのでテストでも外から呼び出す必要がある

        EXPECT_EQ( expected, sut->createJson() );
 
    }
}