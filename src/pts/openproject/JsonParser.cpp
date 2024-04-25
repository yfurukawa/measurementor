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
#include "JsonParser.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "Severity.h"
#include "../../domain/domainPrimitives/MeasurementPrimitives.h"

namespace pts
{

std::list<std::map<std::string, std::string>> JsonParser::collectProjectData(const std::string& jsonString)
{
  std::list<std::map<std::string, std::string>> projectList;
  std::map<std::string, std::string> parsedData;
  projectList.clear();
  auto j = nlohmann::json::parse(jsonString);

  for (int count = 0; count < j["count"]; ++count)
  {
    if(j["_embedded"]["elements"][count]["active"])
    {
      parsedData.insert(std::make_pair("projectId", std::to_string((unsigned int)j["_embedded"]["elements"][count]["id"])));
      parsedData.insert(std::make_pair("projectName", j["_embedded"]["elements"][count]["name"]));
      parsedData.insert(std::make_pair("parentId", ((j["_embedded"]["elements"][count]["_links"]["parent"]["href"]).is_null()
                                                      ? "0"
                                                      : pickupId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"]))));
      projectList.push_back(parsedData);
    }
    parsedData.clear();
  }

  return projectList;
}

std::list<std::map<std::string, std::string>> JsonParser::collectSprintData(const std::string& jsonString)
{
  std::list<std::map<std::string, std::string>> sprintList;
  std::map<std::string, std::string> parsedData;
  sprintList.clear();
  std::string startDate("");
  std::string endDate("");
  auto j = nlohmann::json::parse(jsonString);

  for (int count = 0; count < j["count"]; ++count)
  {
    unsigned int sprintId(j["_embedded"]["elements"][count]["id"]);
    parsedData.insert(std::make_pair("sprintId", std::to_string(sprintId)));
    if ((j["_embedded"]["elements"][count]["_links"]["definingProject"]["href"]).is_null())
    {
      parsedData.insert(std::make_pair("projectId", "0"));
    }
    else
    {
      parsedData.insert(std::make_pair("projectId", pickupId(j["_embedded"]["elements"][count]["_links"]["definingProject"]["href"])));
    }
    parsedData.insert(std::make_pair("sprintName", j["_embedded"]["elements"][count]["name"]));
    parsedData.insert(std::make_pair("status", j["_embedded"]["elements"][count]["status"]));
    if ((j["_embedded"]["elements"][count]["startDate"]).is_null())
    {
      startDate = "1970-01-01T09:00:00+09:00";
    }
    else
    {
      startDate = j["_embedded"]["elements"][count]["startDate"];
      startDate += "T00:00:00+09:00";
    }
    parsedData.insert(std::make_pair("startDate", timeConverter_->convertLocalToGMT(ISO8601String(startDate)).get()));
    if ((j["_embedded"]["elements"][count]["endDate"]).is_null())
    {
      endDate = "1970-01-01T09:00:00+09:00";
    }
    else
    {
      endDate = j["_embedded"]["elements"][count]["endDate"];
      endDate += "T00:00:00+09:00";
    }
    parsedData.insert(std::make_pair("endDate", timeConverter_->convertLocalToGMT(ISO8601String(endDate)).get()));
    sprintList.push_back(parsedData);
    parsedData.clear();
  }

  return sprintList;
}

std::list<std::map<std::string, std::string>> JsonParser::collectItemData(const std::string& jsonString)
{
  std::list<std::map<std::string, std::string>> itemList;
  std::map<std::string, std::string> parsedData;
  itemList.clear();
  auto j = nlohmann::json::parse(jsonString);
  std::string type("");

  for (int count = 0; count < j["count"]; ++count)
  {
    parsedData.clear();
    type = j["_embedded"]["elements"][count]["_links"]["type"]["title"];

    if (type == "Feature")
    {
      unsigned int itemId(j["_embedded"]["elements"][count]["id"]);
      parsedData.insert(std::make_pair("itemId", std::to_string(itemId)));
      parsedData.insert(std::make_pair("itemName", j["_embedded"]["elements"][count]["subject"]));
      parsedData.insert(std::make_pair("projectId", pickupId(j["_embedded"]["elements"][count]["_links"]["project"]["href"])));
      if ((j["_embedded"]["elements"][count]["_links"]["version"]["href"]).is_null())
      {
        // プロダクトバックログに積まれているPBIはスプリントに紐付いていないのでsprintIdは0にする
        parsedData.insert(std::make_pair("sprintId", "0"));
      }
      else
      {
        parsedData.insert(std::make_pair("sprintId", pickupId(j["_embedded"]["elements"][count]["_links"]["version"]["href"])));
      }
      if ((j["_embedded"]["elements"][count]["storyPoints"]).is_null())
      {
        parsedData.insert(std::make_pair("storyPoint", "0"));
      }
      else
      {
        parsedData.insert(std::make_pair("storyPoint", std::to_string(static_cast<int>(j["_embedded"]["elements"][count]["storyPoints"]))));
      }
      parsedData.insert(std::make_pair("status", j["_embedded"]["elements"][count]["_links"]["status"]["title"]));
      parsedData.insert(std::make_pair("statusCode", pickupId(j["_embedded"]["elements"][count]["_links"]["status"]["href"])));
      if ((j["_embedded"]["elements"][count]["derivedEstimatedTime"]).is_null())
      {
        parsedData.insert(std::make_pair("totalEstimatedTime", "0.00"));
      }
      else
      {
        parsedData.insert(std::make_pair("totalEstimatedTime",
                                         pickupHour(j["_embedded"]["elements"][count]["derivedEstimatedTime"])));  // 総見積もり時間が取れる
      }
      itemList.push_back(parsedData);
      parsedData.clear();
    }
  }

  return itemList;
}

std::list<std::map<std::string, std::string>> JsonParser::collectTaskData(const std::string& jsonString)
{
  std::list<std::map<std::string, std::string>> taskList;
  std::map<std::string, std::string> parsedData;
  taskList.clear();
  auto j = nlohmann::json::parse(jsonString);
  std::string type("");

  for (int count = 0; count < j["count"]; ++count)
  {
    parsedData.clear();
    type = j["_embedded"]["elements"][count]["_links"]["type"]["title"];

    if (type == "Task")
    {
      unsigned int taskId(j["_embedded"]["elements"][count]["id"]);
      parsedData.insert(std::make_pair("taskId", std::to_string(taskId)));

      if((j["_embedded"]["elements"][count]["subject"]).is_null())
      {
        parsedData.insert(std::make_pair("taskName", "N/A"));
      }
      else{
        parsedData.insert(std::make_pair("taskName", j["_embedded"]["elements"][count]["subject"]));
      }

      if((j["_embedded"]["elements"][count]["_links"]["parent"]["href"]).is_null())
      {
        parsedData.insert(std::make_pair("itemId", "0"));
      }
      else
      {
        parsedData.insert(std::make_pair("itemId", pickupId(j["_embedded"]["elements"][count]["_links"]["parent"]["href"])));
      }

      if ((j["_embedded"]["elements"][count]["_links"]["version"]["href"]).is_null())
      {
        parsedData.insert(std::make_pair("sprintId", "0"));
        parsedData.insert(std::make_pair("sprintName", ""));
      }
      else
      {
        parsedData.insert(std::make_pair("sprintId", pickupId(j["_embedded"]["elements"][count]["_links"]["version"]["href"])));
        parsedData.insert(std::make_pair("sprintName", j["_embedded"]["elements"][count]["_links"]["version"]["title"]));
      }
      parsedData.insert(std::make_pair("projectId", pickupId(j["_embedded"]["elements"][count]["_links"]["project"]["href"])));
      parsedData.insert(std::make_pair("projectName", j["_embedded"]["elements"][count]["_links"]["project"]["title"]));
      parsedData.insert(std::make_pair("author", j["_embedded"]["elements"][count]["_links"]["author"]["title"]));
      // 見積もり時間はOpenProjectの設定により取得先を変更する必要がありそう
      if ((j["_embedded"]["elements"][count]["remainingTime"]).is_null())
      {
        parsedData.insert(std::make_pair("estimatedTime", "0.00"));
      }
      else
      {
        parsedData.insert(std::make_pair("estimatedTime", pickupHour(j["_embedded"]["elements"][count]["remainingTime"])));
      }
      parsedData.insert(std::make_pair("assignee", (j["_embedded"]["elements"][count]["_links"]["assignee"]["href"]).is_null()
                                                     ? ""
                                                     : j["_embedded"]["elements"][count]["_links"]["assignee"]["title"]));
      parsedData.insert(std::make_pair("status", j["_embedded"]["elements"][count]["_links"]["status"]["title"]));
      parsedData.insert(std::make_pair("statusCode", pickupId(j["_embedded"]["elements"][count]["_links"]["status"]["href"])));
      parsedData.insert(std::make_pair("updatedAt", j["_embedded"]["elements"][count]["updatedAt"]));

      taskList.push_back(parsedData);
      parsedData.clear();
    }
  }
  return taskList;
}

std::string JsonParser::pickupId(std::string href)
{
  auto lastPosition = href.find_last_of("/", href.length());
  std::string idString = href.substr(lastPosition + 1, href.length() - 1 - lastPosition);
  return std::to_string(std::stoi(idString));
}

std::string JsonParser::pickupHour(std::string remainingTimeValue)
{
  std::regex re(R"(P((\d{1,2})D)*T?((\d{1,2})H)*((\d{1,2})M)*((\d{1,2})S)*)");
  std::cmatch match;
  std::regex_match(remainingTimeValue.c_str(), match, re);
  if (match.empty())
  {
    AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[JsonParser] : RemainingTime pattern is unmatched " + remainingTimeValue, AbstLogger::Severity::error);
  }
  double day = match.length(2) != 0 ? std::stod(match.str(2)) : static_cast<double>(0);
  double hour = match.length(4) != 0 ? std::stod(match.str(4)) : static_cast<double>(0);
  double min = match.length(6) != 0 ? std::stod(match.str(6)) : static_cast<double>(0);
  double remainingTime = day * 24 + hour + min / 60;

  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << remainingTime;
  return ss.str();
  ;
}

}  // namespace pts
