#include <string>
#include "JsonCreatorTest.h"
#include "../../src/domain/JsonCreator.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

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

TEST_F(JsonCreatorTest, createJsonFromStringValue)
{
  JsonKey key("testKey");
  std::string value("testValue");
  std::string expect(R"({"testKey":"testValue"})");

  sut->holdData(key, value);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonFromMultiStringValue)
{
  JsonKey key1("testKey1");
  JsonKey key2("testKey2");
  std::string value("testValue");
  std::string expect(R"({"testKey1":"testValue","testKey2":"testValue"})");

  sut->holdData(key1, value);
  sut->holdData(key2, value);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonFromIntValue)
{
  JsonKey key("testKey");
  int value(1);
  std::string expect(R"({"testKey":1})");

  sut->holdData(key, value);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonFromStringAndIntValue)
{
  JsonKey key1("testKey1");
  JsonKey key2("testKey2");
  std::string stringValue("testValue");
  int value(1);
  std::string expect(R"({"testKey1":"testValue","testKey2":1})");

  sut->holdData(key1, stringValue);
  sut->holdData(key2, value);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonFromBoolValue)
{
  JsonKey key("testKey");
  bool boolValue(true);

  std::string expect(R"({"testKey":true})");

  sut->holdData(key, boolValue);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonFromNumberValue)
{
  JsonKey key1("testKey1");
  JsonKey key2("testKey2");
  JsonKey key3("testKey3");
  int intValue(1);
  long longValue(2L);
  double doubleValue(3.14159265);

  std::string expect(R"({"testKey1":1,"testKey2":2,"testKey3":3.14159265})");

  sut->holdData(key1, intValue);
  sut->holdData(key2, longValue);
  sut->holdData(key3, doubleValue);

  EXPECT_EQ(expect, sut->createJson());
}

TEST_F(JsonCreatorTest, createJsonNested)
{
  std::string key("testKey");
  double doubleValue(3.14159265);

  JsonKey parentKey("parentKey");
  std::string parentValue("parentValue");
  std::string expect(
    R"({"child":[{"testKey1":1,"testKey2":2,"testKey3":3.14159265},{"testKey21":21,"testKey22":22,"testKey23":3.14159265}],"parentKey":"parentValue"})");

  nlohmann::json child1;
  child1[key + "1"] = 1;
  child1[key + "2"] = 2;
  child1[key + "3"] = doubleValue;
  JsonObject childJson1(child1.dump());
  nlohmann::json child2;

  child2[key + "21"] = 21;
  child2[key + "22"] = 22;
  child2[key + "23"] = doubleValue;
  JsonObject childJson2(child2.dump());

  JsonKey childKey("child");

  sut->holdData(parentKey, parentValue);
  sut->holdDataAsArray(childKey, childJson1);
  sut->holdDataAsArray(childKey, childJson2);

  EXPECT_EQ(expect, sut->createJson());
}
}  // namespace measurementor