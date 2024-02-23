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
        //( Id id, Name name,  )
        Id id(1);
        Name name("Test Sprint");
        ProjectId projectId(10);
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
         
        sut = new Sprint( id, name, startDate, endDate );

        std::string expected(R"({"endDate":"2024-02-25T12:34:56+09:00","id":1,"name":"Test Sprint","projectId":0,"startDate":"2024-02-23T12:34:56+09:00","status":"","totalStoryPoint":0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }
/*
    TEST_F(SprintTest, createJson_OneTask)
    {
        Id taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        SprintId SprintId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status taskStatus("In Progress");
        StatusCode statusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        std::shared_ptr<Task> task = std::make_shared<Task>( taskId, taskName, author, SprintId, estimatedTime, assignee, taskStatus, statusCode, updatedAt );

        Id id(1);
        Name name("Test Sprint");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("open");
        SprintId sprintId(12);
 
        sut = new Sprint( id, name, projectId, sprintId, storyPoint, status );

        sut->addTask( task );

        std::string expected(R"({"id":1,"name":"Test Sprint","projectId":10,"sprintId":12,"status":"open","storyPoint":3,"task":[{"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"SprintId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"}],"totalEstimatedTime":5.5})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }
*/
}