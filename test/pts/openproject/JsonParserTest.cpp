#include <fstream>
#include <map>
#include <string>
#include "JsonParserTest.h"
#include "../../../src/pts/openproject/JsonParser.h"
//#include "../../../lib/libClock.h"

namespace pts
{
    void JsonParserTest::SetUp()
    {
        sut = new JsonParser();
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
        EXPECT_EQ(1, result.size() );
        EXPECT_EQ( expect, result.front() );
        
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
            {"storyPoint","3"}
        };

        std::list<std::map<std::string, std::string>> result = sut->collectItemData( testJson );
        EXPECT_EQ(1, result.size() );
        EXPECT_EQ( expect, result.front() );
        
    }

}
