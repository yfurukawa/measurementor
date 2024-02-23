#include <sstream>
#include "JsonCreator.h"

namespace measurementor
{
JsonCreator::JsonCreator()
{
    jsonRaw_.clear();
}

void JsonCreator::holdData(std::string key, std::string stringValue)
{
    jsonRaw_[key] = stringValue;
}

void JsonCreator::holdData(std::string key, int intValue)
{
    jsonRaw_[key] = intValue;
}

void JsonCreator::holdData(std::string key, long longValue)
{
    jsonRaw_[key] = longValue;
}

void JsonCreator::holdData(std::string key, double doubleValue)
{
    jsonRaw_[key] = doubleValue;
}

void JsonCreator::holdData(std::string key, bool boolValue)
{
    jsonRaw_[key] = boolValue;
}

std::string JsonCreator::createJson()
{
    std::ostringstream ss("");
    ss << jsonRaw_;
    return ss.str();
}

}