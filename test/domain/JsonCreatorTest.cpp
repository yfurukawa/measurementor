#include <string>
#include "JsonCreatorTest.h"
#include "../../src/domain/JsonCreator.h"

namespace measurementor
{
    void JsonCreatorTest::SetUp()
    {
        sut = new JsonCreator();
    }

    void JsonCreatorTest::TearDown()
    {
        delete sut;
    }

    TEST_F( JsonCreatorTest, createJsonFromStringValue)
    {
        std::string key("testKey");
        std::string value("testValue");
        std::string expect(R"({"testKey":"testValue"})");
        sut->holdData(key, value);
        EXPECT_EQ( expect, sut->createJson() );
    }
    
    TEST_F( JsonCreatorTest, createJsonFromMultiStringValue)
    {
        std::string key("testKey");
        std::string value("testValue");
        std::string expect(R"({"testKey1":"testValue","testKey2":"testValue"})");
        
        sut->holdData(key + "1", value);
        sut->holdData(key + "2", value);
        
        EXPECT_EQ( expect, sut->createJson() );
    }

    TEST_F( JsonCreatorTest, createJsonFromIntValue)
    {
        std::string key("testKey");
        int value(1);
        std::string expect(R"({"testKey":1})");
        
        sut->holdData(key, value);
                
        EXPECT_EQ( expect, sut->createJson() );
    }

    TEST_F( JsonCreatorTest, createJsonFromStringAndIntValue)
    {
        std::string key("testKey");
        std::string stringValue("testValue");
        int value(1);
        std::string expect(R"({"testKey1":"testValue","testKey2":1})");
        
        sut->holdData(key + "1", stringValue);
        sut->holdData(key + "2", value);
                
        EXPECT_EQ( expect, sut->createJson() );
    }
}