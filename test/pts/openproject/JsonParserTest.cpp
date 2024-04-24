#include <fstream>
#include <map>
#include <string>
#include "JsonParserTest.h"
#include "JsonParserSpy.h"
//#include "../../../lib/libClock.h"

namespace pts
{
    void JsonParserTest::SetUp()
    {
        sut = new JsonParserSpy();
    }

    void JsonParserTest::TearDown()
    {
        delete sut;
    }

    TEST_F(JsonParserTest, collectTaskData_oneTask)
    {
        std::ifstream ifs("./oneTask.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"assignee","Yoshihiro Furukawa"},
            {"author","Yoshihiro Furukawa"},
            {"estimatedTime","4.00"},
            {"itemId","37"},
            {"taskName","test Tsk"},
            {"projectId","3"},
            {"projectName","TestProject1"},
            {"sprintId","5"},
            {"sprintName","Sprint1 of Test Project"},
            {"status","New"},
            {"statusCode","1"},
            {"taskId","38"},
            {"updatedAt","2024-03-02T07:14:24.773Z"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectTaskData( testJson );
        EXPECT_EQ(1, result.size() );
        EXPECT_EQ( expect, result.front() );
        
    }

    TEST_F(JsonParserTest, collectTaskData_manyTask)
    {
        std::ifstream ifs("./severalTask.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"assignee","Yoshihiro Furukawa"},
            {"author","Yoshihiro Furukawa"},
            {"estimatedTime","4"},
            {"itemId","37"},
            {"taskName","test Tsk"},
            {"projectId","3"},
            {"sprintId","5"},
            {"status","New"},
            {"statusCode","1"},
            {"taskId","38"},
            {"updatedAt","2024-03-02T07:14:24.773Z"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectTaskData( testJson );
        EXPECT_EQ(5, result.size() );

    }

    TEST_F(JsonParserTest, collectItemData_oneItem)
    {
        std::ifstream ifs("./oneItem.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"itemId","37"},
            {"itemName","Test Feature"},
            {"projectId","3"},
            {"sprintId","5"},
            {"status","New"},
            {"statusCode","1"},
            {"storyPoint","3"},
            {"totalEstimatedTime","4.00"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectItemData( testJson );
        EXPECT_EQ(1, result.size() );
        EXPECT_EQ( expect, result.front() );
        
    }

TEST_F(JsonParserTest, collectItemData_manyItem)
    {
        std::ifstream ifs("./severalTask.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"itemId","37"},
            {"itemName","Test Feature"},
            {"projectId","3"},
            {"sprintId","5"},
            {"status","New"},
            {"statusCode","1"},
            {"storyPoint","3"},
            {"totalEstimatedTime","4.00"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectItemData( testJson );
        EXPECT_EQ(4, result.size() );
        
    }

    TEST_F(JsonParserTest, collectItemData_oneSprint)
    {
        std::ifstream ifs("./oneSprint.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"endDate","2024-03-05T15:00:00Z"},
            {"sprintName","Sprint1 of Test Project"},
            {"projectId","3"},
            {"startDate","2024-02-26T15:00:00Z"},
            {"sprintId","5"},
            {"status","open"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectSprintData( testJson );
        EXPECT_EQ(1, result.size() );
        EXPECT_EQ( expect, result.front() );
        
    }

    TEST_F(JsonParserTest, collectItemData_manySprint)
    {
        std::ifstream ifs("./severalVersions.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::map<std::string, std::string> expect{
            {"endDate","2024-03-06"},
            {"sprintName","Sprint1 of Test Project"},
            {"projectId","3"},
            {"startDate","2024-02-27"},
            {"sprintId","5"},
            {"status","open"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectSprintData( testJson );
        EXPECT_EQ(3, result.size() );
        
    }

    TEST_F(JsonParserTest, collectItemData_Project)
    {
        std::ifstream ifs("./availableProjects.json");
        std::string testJson("");
        std::getline(ifs, testJson);
        std::list<std::map<std::string, std::string>> expect
        {
            {
                {"projectName","Demo project"},
                {"projectId","1"},
                {"parentId","0"}
            },
            {
                {"projectName","Scrum project"},
                {"projectId","2"},
                {"parentId","0"}
            },
            {
                {"projectName","TestProject1"},
                {"projectId","3"},
                {"parentId","0"}
            }
        };

        std::list<std::map<std::string, std::string>> result = sut->collectProjectData( testJson );
        EXPECT_EQ(3, result.size() );
        EXPECT_EQ( expect, result );
        
    }
}
