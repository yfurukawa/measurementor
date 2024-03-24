/*!
 @file  PreviousDataReader.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <filesystem>
#include "JsonParser.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "PreviousDataReader.h"
#include "Severity.h"
#include "TextFileReader.h"

namespace pts
{

PreviousDataReader::PreviousDataReader()
  : previousDataReader_(std::make_unique<TextFileReader>()), jsonParser_(std::make_unique<JsonParser>())
{
}

std::list<std::map<std::string, std::string>> PreviousDataReader::preparePreviousTaskData(const measurementor::ProjectId& projectId)
{
  std::list<std::map<std::string, std::string>> previousTask;
  previousTask.clear();
  std::filesystem::path previousFile("previousTask_" + std::to_string(projectId.get()) + ".json");
  auto openError = previousDataReader_->openFile(previousFile);
  if (openError)
  {
    AbstLogger::LoggerFactory::getInstance()->createLogger()->log(
      "[PreviousDataReader] : previous file open err : " + previousFile.string() + " " + openError.value(), AbstLogger::Severity::error);
    return previousTask;
  }

  std::optional<std::string> readResult;
  bool read(false);
  while (!read)
  {
    readResult = previousDataReader_->readLine();
    if (readResult)
    {
      previousTask = jsonParser_->collectTaskData(readResult.value());
      read = true;
    }
    else
    {
      AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[PreviousDataReader] : " + previousFile.string() + " read err",
                                                                    AbstLogger::Severity::error);
      read = true;
    }
  }
  previousDataReader_->closeFile();
  return previousTask;
}

}  // namespace pts
