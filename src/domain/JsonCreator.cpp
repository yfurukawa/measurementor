/*!
 @file JsonCreator.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "JsonCreator.h"

namespace measurementor
{

JsonCreator::JsonCreator()
{
  jsonRaw_.clear();
}

void JsonCreator::holdData(JsonKey key, std::string stringValue)
{
  jsonRaw_[key.get()] = stringValue;
}

void JsonCreator::holdData(JsonKey key, int intValue)
{
  jsonRaw_[key.get()] = intValue;
}

void JsonCreator::holdData(JsonKey key, std::uint_fast16_t intValue)
{
  jsonRaw_[key.get()] = intValue;
}

void JsonCreator::holdData(JsonKey key, long longValue)
{
  jsonRaw_[key.get()] = longValue;
}

void JsonCreator::holdData(JsonKey key, double doubleValue)
{
  jsonRaw_[key.get()] = doubleValue;
}

void JsonCreator::holdData(JsonKey key, bool boolValue)
{
  jsonRaw_[key.get()] = boolValue;
}

void JsonCreator::holdData(JsonKey key, JsonObject jsonObject)
{
  jsonRaw_[key.get()] = nlohmann::json::parse(jsonObject.get());
}

void JsonCreator::holdDataAsArray(JsonKey key, JsonObject jsonObject)
{
  nlohmann::json childJson = nlohmann::json::parse(jsonObject.get());

  if (jsonRaw_[key.get()].is_null())
  {
    nlohmann::json jsonArray = nlohmann::json::array();
    jsonArray.emplace_back(childJson);
    jsonRaw_[key.get()] = jsonArray;
  }
  else if (jsonRaw_[key.get()].is_array())
  {
    jsonRaw_[key.get()].emplace_back(childJson);
  }
}

std::string JsonCreator::createJson()
{
  return jsonRaw_.dump();
}

}  // namespace measurementor