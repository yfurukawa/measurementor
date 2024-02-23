#include <sstream>
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

std::string JsonCreator::createJson()
{
    return jsonRaw_.dump();
}

}