/*!
 @file      JsonParser.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include "ISO8601String.h"
#include "JsonParserSpy.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "Severity.h"
#include "../../../src/domain/domainPrimitives/MeasurementPrimitives.h"

namespace pts
{

std::list<std::map<std::string, std::string>> JsonParserSpy::collectProjectData(const std::string& jsonString)
{
  return JsonParser::collectProjectData(jsonString);
}

std::list<std::map<std::string, std::string>> JsonParserSpy::collectSprintData(const std::string& jsonString)
{
  return JsonParser::collectSprintData(jsonString);
}

std::list<std::map<std::string, std::string>> JsonParserSpy::collectItemData(const std::string& jsonString)
{
  return JsonParser::collectItemData(jsonString);
}

std::list<std::map<std::string, std::string>> JsonParserSpy::collectTaskData(const std::string& jsonString)
{
  return JsonParser::collectTaskData(jsonString);
}

std::string JsonParserSpy::pickupId(std::string href)
{
  return JsonParser::pickupId(href);
}

std::string JsonParserSpy::pickupHour(std::string remainingTimeValue)
{
  return JsonParser::pickupHour(remainingTimeValue);
}

}  // namespace pts
