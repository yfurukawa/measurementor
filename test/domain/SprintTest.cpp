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
        ProjectId projectId(10);
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
         
        sut = new Sprint( id, name, startDate, endDate );

        std::string expected(R"({"endDate":"2024-02-25T12:34:56+09:00","id":1,"name":"Test Sprint","projectId":0,"remainingWorkTime":0.0,"startDate":"2024-02-23T12:34:56+09:00","status":"","totalStoryPoint":0})");

        EXPECT_EQ( expected, sut->createJson() );
 
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
        Status status("open");
        StatusCode statusCode(1);
        SprintId sprintId(12);
 
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, sprintId, storyPoint, status, statusCode );

        item->addTask( task );

        // Sprint
        Id id(1);
        Name name("Test Sprint");
        ProjectId projectId(10);
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
        sut = new Sprint( id, name, startDate, endDate );        

        sut->addItem( item );

        std::string expected(R"({"endDate":"2024-02-25T12:34:56+09:00","id":1,"item":[{"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"open","statusCode":1,"storyPoint":3,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":5.5}],"name":"Test Sprint","projectId":0,"remainingWorkTime":5.5,"startDate":"2024-02-23T12:34:56+09:00","status":"","totalStoryPoint":0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }

}