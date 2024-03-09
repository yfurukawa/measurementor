#include <string>
#include "ProjectTest.h"
#include "../../src/domain/Project.h"

namespace measurementor
{
    void ProjectTest::SetUp()
    {
    }

    void ProjectTest::TearDown()
    {
        delete sut;
    }

    TEST_F(ProjectTest, createJson_EmptyProject)
    {
        ProjectId projectId(1);
        Name projectName("Test Project");
        ProjectId parentId(10);
        Timestamp timestamp("2024-02-26T12:34:56.000");
         
        sut = new Project( projectId, projectName, parentId, timestamp );

        std::string expected(R"({"name":"Test Project","projectId":1,"remainingStoryPoints":0,"timestamp":"2024-02-26T12:34:56.000"})");

        EXPECT_EQ( expected, sut->createJson() );
    }

}