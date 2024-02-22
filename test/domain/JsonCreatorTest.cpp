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
}