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

std::string JsonCreator::createJson()
{
    std::ostringstream ss("");
    ss << jsonRaw_;
    return ss.str();
}

}