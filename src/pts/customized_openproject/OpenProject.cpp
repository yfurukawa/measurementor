/*!
 @file  OpenProject.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <cstdlib>
#include <fstream>
#include <string>
#include "OpenProject.h"
#include "../../domain/Project.h"
#include "JsonParser.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "RestAPIHelper.h"
#include "TextFileWriter.h"
#include "nlohmann/json.hpp"

namespace pts
{

OpenProject::OpenProject(ApiKey apiKey, std::string destination, unsigned int destinationPort)
  : apiKey_(apiKey)
  , destination_(destination)
  , destinationPort_(destinationPort)
  , previousDataWriter_(std::make_unique<::TextFileWriter>())
  , jsonParser_(std::make_unique<JsonParser>())
  , loggerFactory_(AbstLogger::LoggerFactory::getInstance())
  , logger_(loggerFactory_->createLogger())
{
}

std::list<std::map<std::string, std::string>> OpenProject::collectAllActiveProject()
{
  std::string message("GET /api/v3/projects?pageSize=1000");
  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousProject.json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectProjectData(receivedJson);
}

std::list<std::map<std::string, std::string>> OpenProject::collectSprintInformation(const measurementor::ProjectId& projectId)
{
  std::string message("/api/v3/projects/" + std::to_string(projectId.get()) + "/versions");
  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousSprint_" + std::to_string(projectId.get()) + ".json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectSprintData(receivedJson);
}

std::list<std::map<std::string, std::string>> OpenProject::collectItemInformation(const measurementor::ProjectId& projectId)
{
  // filter : [
  //            {"type":{"operator":"=","values":["4"]}},
  //            {"status":{"operator":"=","values":["1","7","15"]}}
  //          ]
  // Featureのみを取得するようにしている。
  // ページサイズは、OpenProjectの設定に依存する
  std::string message("/api/v3/projects/" + std::to_string(projectId.get()) +
                      "/work_packages?pageSize=4000&filters=%5b%7b%22type%22:%7b%22operator%22:%22=%22,%22values%22:%5b%224%22%5d%7d%7d,%7b%22status%22:%7b%22operator%22:%22=%22,%22values%22:%5b%221%22,%227%22,%2215%22%5d%7d%7d%5d");
  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousItem_" + std::to_string(projectId.get()) + ".json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectItemData(receivedJson);
}

std::list<std::map<std::string, std::string>> OpenProject::collectTaskInformation(const measurementor::ProjectId& projectId)
{
  // filter : [
  //            {"type":{"operator":"=","values":["1"]}},
  //            {"status":{"operator":"=","values":["1","7","12","15"]}}
  //          ]
  // タスクの状態が、New、In Progress、Closed及びReviewのものを取得するようにしている。
  // このフィルタがないと、statusがClosedのタスクは取得できない。
  // ページサイズは、OpenProjectの設定に依存する
  std::string message("/api/v3/projects/" + std::to_string(projectId.get()) +
                      "/work_packages?pageSize=4000&filters=%5b%7b%22type%22:%7b%22operator%22:%22=%22,%22values%22:%5b%221%22%5d%7d%7d,%7b%22status%22:%7b%22operator%22:%22=%22,%22values%22:%5b%221%22,%227%22,%2212%22,%2215%22%5d%7d%7d%5d");

  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousTask_" + std::to_string(projectId.get()) + ".json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectTaskData(receivedJson);
}

std::string OpenProject::sendQueryMessage(std::string queryMessage)
{
  std::string command("/usr/bin/curl -s -u apikey:" + apiKey_.get() + " http://" + destination_ + ":" + std::to_string(destinationPort_) + queryMessage + " -o temp.json");
  AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[OpenProject] : " + command);
  system(command.c_str());

  std::ifstream tempJson("temp.json");
  nlohmann::json temp;
  tempJson >> temp;

  return temp.dump();
}

void OpenProject::saveJsonObjectAsPreviousData(std::filesystem::path previousFile, const std::string& receivedJson)
{
  previousDataWriter_->openFile(previousFile);
  auto writeError = previousDataWriter_->write(receivedJson);
  if (writeError)
  {
    std::cout << writeError.value() << std::endl;
  }

  // 末尾に改行がないと次に読み込めないので改行を追加する
  writeError = previousDataWriter_->write("\n");
  if (writeError)
  {
    std::cout << writeError.value() << std::endl;
  }
  previousDataWriter_->closeFile();
}

}  // namespace pts
