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
        Status status("open");
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"open","storyPoint":3,"totalEstimatedTime":0.0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }

    TEST_F(ItemTest, createJson_OneTask)
    {
        Id taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode statusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, itemId, estimatedTime, assignee, taskStatus, statusCode, updatedAt );

        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("open");
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status );

        sut->addTask( task );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"open","storyPoint":3,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":5.5})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }
}