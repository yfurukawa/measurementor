#include <string>
#include "TaskTest.h"
#include "../../src/domain/Task.h"

namespace measurementor
{
    void TaskTest::SetUp()
    {
    }

    void TaskTest::TearDown()
    {
        delete sut;
    }

    TEST_F(TaskTest, createJson)
    {
        Timestamp timestamp("2024-02-27T12:34:56.123");
        ProjectId projectId(1);
        SprintId sprintId(11);
        ItemId itemId(1);
        TaskId taskId(11);
        Name taskName("Test Task");
        Author author("Test Author");
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status status("In Progress");
        StatusCode statusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        
        sut = new measurementor::Task( projectId, sprintId, itemId, taskId, taskName, author, estimatedTime, assignee, status, statusCode, updatedAt );

        std::string expected(R"({"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"itemId":1,"projectId":1,"sprintId":11,"status":"In Progress","statusCode":2,"taskId":11,"taskName":"Test Task","timestamp":"2024-02-27T12:34:56.123","updatedAt":"2024-02-23T19:18:25+09:00"})");

        EXPECT_EQ( expected, sut->createJson( timestamp ) );
    }

}