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
  , starDateOnReview_("")
  , inProgressDuration_(0.0)
{
}

void RepositoryMock::registerMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData)
{
  metricsData_ = metricsData;
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
  if(starDateOnReview_ != "")
  {
    measurementor::UpdatedAt date{starDateOnReview_};
    return date; 
  }
  else
  {
    return std::nullopt;
  }
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnClose(measurementor::TaskId taskId)
{
  return std::nullopt;
}

double RepositoryMock::getInProgressDuration(measurementor::TaskId taskId)
{
  return inProgressDuration_;
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

void RepositoryMock::setStarDateOnReview(std::string date)
{
  starDateOnReview_ = std::move(date);
}

void RepositoryMock::setInProgressDuration(double duration)
{
  inProgressDuration_ = duration;
}

std::string RepositoryMock::getMetricsData()
{
  return metricsData_.dump();
}

void RepositoryMock::clear()
{
  starDateOnInProgress_ = "";
  starDateOnReview_ = "";
  inProgressDuration_ = 0;
  metricsData_ = nullptr;
}

}  // namespace repository