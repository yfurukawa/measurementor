/*!
 @file      RepositoryMock.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <sstream>
#include "RepositoryMock.h"

namespace repository
{

RepositoryMock::RepositoryMock()
  : starDateOnInProgress_("")
{
}

void RepositoryMock::registerMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData)
{
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnInProgress(measurementor::TaskId taskId)
{
  if(starDateOnInProgress_ != "")
  {
    measurementor::UpdatedAt date{starDateOnInProgress_};
    return date; 
  }
  else
  {
    return std::nullopt;
  }
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnReview(measurementor::TaskId taskId)
{
  return std::nullopt;
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnClose(measurementor::TaskId taskId)
{
  return std::nullopt;
}

double RepositoryMock::getInProgressDuration(measurementor::TaskId taskId)
{
  return 0;
}

void RepositoryMock::updateMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData)
{
}

void RepositoryMock::deleteMetricsData(measurementor::TaskId taskId)
{
}

void RepositoryMock::sendCommand(std::string command)
{
}

nlohmann::json RepositoryMock::sendQuery(measurementor::TaskId taskId)
{
  return nlohmann::json{};
}

void RepositoryMock::setStarDateOnInProgress(std::string date)
{
  starDateOnInProgress_ = std::move(date);
}

}  // namespace repository