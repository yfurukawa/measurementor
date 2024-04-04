/*!
 @file      Repository.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <string>
#include "ITcpClient.h"
#include "Repository.h"
#include "TextFileWriter.h"

namespace repository
{

void Repository::registerMetricsData(TaskId taskId, nlohmann::json metricsData)
{

}

nlohmann::json Repository::getInProgressStartedDate(measurementor::TaskId taskId)
{
  nlohmann::json metricsData("");
  return metricsData;
}

}  // repository