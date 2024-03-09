#include "JsonCreator.h"

namespace measurementor
{

JsonCreator::JsonCreator()
{
    jsonRaw_.clear();
}

inline void JsonCreator::holdData(JsonKey key, std::string stringValue)
{
    jsonRaw_[key.get()] = stringValue;
}

inline void JsonCreator::holdData(JsonKey key, int intValue)
{
    jsonRaw_[key.get()] = intValue;
}

inline void JsonCreator::holdData(JsonKey key, unsigned int intValue)
{
    jsonRaw_[key.get()] = intValue;
}

inline void JsonCreator::holdData(JsonKey key, long longValue)
{
    jsonRaw_[key.get()] = longValue;
}

inline void JsonCreator::holdData(JsonKey key, double doubleValue)
{
    jsonRaw_[key.get()] = doubleValue;
}

inline void JsonCreator::holdData(JsonKey key, bool boolValue)
{
    jsonRaw_[key.get()] = boolValue;
}

inline void JsonCreator::holdData(JsonKey key, JsonObject jsonObject)
{
    jsonRaw_[key.get()] = nlohmann::json::parse(jsonObject.get());
}

void JsonCreator::holdDataAsArray(JsonKey key, JsonObject jsonObject)
{
    nlohmann::json childJson = nlohmann::json::parse(jsonObject.get());

    if( jsonRaw_[key.get()].is_null())
    {
        nlohmann::json jsonArray = nlohmann::json::array();
        jsonArray.emplace_back(childJson);
        jsonRaw_[key.get()] = jsonArray;
    }
    else if( jsonRaw_[key.get()].is_array() )
    {
        jsonRaw_[key.get()].emplace_back( childJson );
    }

}

inline std::string JsonCreator::createJson()
{
    return jsonRaw_.dump();
}

}