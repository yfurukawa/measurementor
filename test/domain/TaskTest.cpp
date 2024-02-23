#include <string>
#include "TaskTest.h"
#include "../../src/domain/Task.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

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
        Id id(11);
        Name name("Test Task");
        Author author("Test Author");
        ItemId itemId(1);
        EstimatedTime estimatedTime(5.5);
        Assignee assignee("Test Assignee");
        Status status("In Progress");
        StatusCode statusCode(2);
        UpdatedAt updatedAt("2024-02-23T19:18:25+09:00");
        sut = new Task( id, name, author, itemId, estimatedTime, assignee, status, statusCode, updatedAt );

        std::string expected(R"({"assignee":"Test Assignee","author":"Test Author","estimatedTime":5.5,"id":11,"itemId":1,"name":"Test Task","status":"In Progress","statusCode":2,"updatedAt":"2024-02-23T19:18:25+09:00"})");

        EXPECT_EQ( expected, sut->createJson() );
    }

}