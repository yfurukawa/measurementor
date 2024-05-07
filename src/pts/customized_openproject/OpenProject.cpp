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
#include "Severity.h"
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
  std::string message("/api/v3/projects?pageSize=1000");
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
  //            {"type":{"operator":"=","values":["9"]}},
  //            {"status":{"operator":"=","values":["15","16","17"]}}
  //          ]
  // Featureのみを取得するようにしている。
  // また、Itemの状態は、新規(15)、進行中(16)およびレビュー中(17)に限定している
  // ページサイズは、OpenProjectの設定に依存する
  std::string message("/api/v3/projects/" + std::to_string(projectId.get()) +
                      "/work_packages?pageSize=4000&filters=%5b%7b%22type%22:%7b%22operator%22:%22=%22,%22values%22:%5b%229%22%5d%7d%7d,
                      %7b%22status%22:%7b%22operator%22:%22=%22,%22values%22:%5b%2215%22,%2216%22,%2217%22%5d%7d%7d%5d");
  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousItem_" + std::to_string(projectId.get()) + ".json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectItemData(receivedJson);
}

std::list<std::map<std::string, std::string>> OpenProject::collectTaskInformation(const measurementor::ProjectId& projectId)
{
  // filter : [
  //            {"type":{"operator":"=","values":["8"]}},
  //            {"status":{"operator":"=","values":["15","16","17","18","19"]}}
  //          ]
  // タスクの状態が、新規(15)、進行中(16)、レビュー中(17)、解決(18)及び終了(19)のものを取得するようにしている。
  // このフィルタがないと、statusがClosedのタスクは取得できない。
  // ページサイズは、OpenProjectの設定に依存する
  std::string message("/api/v3/projects/" + std::to_string(projectId.get()) +
                      "/work_packages?pageSize=4000&filters=%5b%7b%22type%22:%7b%22operator%22:%22=%22,%22values%22:%5b%228%22%5d%7d%7d,
                      %7b%22status%22:%7b%22operator%22:%22=%22,%22values%22:%5b%2215%22,%2216%22,%2217%22,%2218%22,%2219%22%5d%7d%7d%5d");

  std::string receivedJson = sendQueryMessage(message);

  std::filesystem::path previousFile("previousTask_" + std::to_string(projectId.get()) + ".json");
  saveJsonObjectAsPreviousData(previousFile, receivedJson);
  return jsonParser_->collectTaskData(receivedJson);
}

std::string OpenProject::sendQueryMessage(std::string queryMessage)
{
  std::string command("/usr/bin/curl -s -o temp.json -u apikey:" + apiKey_.get() + " http://" + destination_ + ":" + std::to_string(destinationPort_) + queryMessage);
  AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[OpenProject] : " + command);
  system(command.c_str());

  // systemコマンドの戻り値ではサーバから取得したデータを戻せないため、
  // curlで取得したデータを一時ファイル（temp.json）に保存してある。このため、改めてそこからデータを読み込む
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
    AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[OpenProject][previous data write] : " + writeError.value(), AbstLogger::Severity::error);
  }

  // 末尾に改行がないと次に読み込めないので改行を追加する
  writeError = previousDataWriter_->write("\n");
  if (writeError)
  {
    AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[OpenProject][CR write] : " + writeError.value(), AbstLogger::Severity::error);
  }
  previousDataWriter_->closeFile();
}

}  // namespace pts
