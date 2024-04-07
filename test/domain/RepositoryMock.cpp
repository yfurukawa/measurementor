/*!
 @file      RepositoryMock.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <sstream>
#include "RepositoryMock.h"

namespace repository
{

RepositoryMock::RepositoryMock()
{
  loggerFactory_ = AbstLogger::LoggerFactory::getInstance();
  logger_ = loggerFactory_->createLogger();
}
/*
RepositoryMock::RepositoryMock(std::string userName, std::string password, std::string hostName, std::string port, std::string databaseName,
                       std::string tableName)
  : userName_(userName)
  , password_(password)
  , hostName_(hostName)
  , port_(port)
  , databaseName_(databaseName)
  , tableName_(tableName)
{
  loggerFactory_ = AbstLogger::LoggerFactory::getInstance();
  logger_ = loggerFactory_->createLogger();
}
*/
void RepositoryMock::registerMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData)
{
  //logger_->log(metricsData.dump());
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnInProgress(measurementor::TaskId taskId)
{
  /*
  try
  {
    nlohmann::json result = sendQuery(taskId);
    if (result["InProgressStartDate"].is_null())
    {
      return std::nullopt;
    }
    else
    {
      return measurementor::UpdatedAt{result["InProgressStartDate"]};
    }
  }
  catch (pqxx::sql_error const& e)
  {
    std::stringstream errorStream;
    std::stringstream queryStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : SQL error: " << e.what();
    queryStream << "[Repositoruy][getStarDateOnInProgress] : Query was: " << e.query();
    logger_->log(errorStream.str());
    logger_->log(queryStream.str());
    return std::nullopt;
  }
  catch (std::exception const& e)
  {
    std::stringstream errorStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : Error: " << e.what();
    logger_->log(errorStream.str());
    return std::nullopt;
  }
  */
  return std::nullopt;
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnReview(measurementor::TaskId taskId)
{
  /*
  try
  {
    nlohmann::json result = sendQuery(taskId);
    if (result["ReviewStartDate"].is_null())
    {
      return std::nullopt;
    }
    else
    {
      return measurementor::UpdatedAt{result["ReviewStartDate"]};
    }
  }
  catch (pqxx::sql_error const& e)
  {
    std::stringstream errorStream;
    std::stringstream queryStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : SQL error: " << e.what();
    queryStream << "[Repositoruy][getStarDateOnInProgress] : Query was: " << e.query();
    logger_->log(errorStream.str());
    logger_->log(queryStream.str());
    return std::nullopt;
  }
  catch (std::exception const& e)
  {
    std::stringstream errorStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : Error: " << e.what();
    logger_->log(errorStream.str());
    return std::nullopt;
  }
  */
  return std::nullopt;
}

std::optional<measurementor::UpdatedAt> RepositoryMock::getStarDateOnClose(measurementor::TaskId taskId)
{
  /*
  try
  {
    nlohmann::json result = sendQuery(taskId);
    if (result["CloseDate"].is_null())
    {
      return std::nullopt;
    }
    else
    {
      return measurementor::UpdatedAt{result["CloseDate"]};
    }
  }
  catch (pqxx::sql_error const& e)
  {
    std::stringstream errorStream;
    std::stringstream queryStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : SQL error: " << e.what();
    queryStream << "[Repositoruy][getStarDateOnInProgress] : Query was: " << e.query();
    logger_->log(errorStream.str());
    logger_->log(queryStream.str());
    return std::nullopt;
  }
  catch (std::exception const& e)
  {
    std::stringstream errorStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : Error: " << e.what();
    logger_->log(errorStream.str());
    return std::nullopt;
  }
  */
  return std::nullopt;
}

double RepositoryMock::getInProgressDuration(measurementor::TaskId taskId)
{
  /*
  try
  {
    nlohmann::json result = sendQuery(taskId);
    return result["InProgressDuration"];
  }
  catch (pqxx::sql_error const& e)
  {
    std::stringstream errorStream;
    std::stringstream queryStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : SQL error: " << e.what();
    queryStream << "[Repositoruy][getStarDateOnInProgress] : Query was: " << e.query();
    logger_->log(errorStream.str());
    logger_->log(queryStream.str());
    return 0;
  }
  catch (std::exception const& e)
  {
    std::stringstream errorStream;
    errorStream << "[Repositoruy][getStarDateOnInProgress] : Error: " << e.what();
    logger_->log(errorStream.str());
    return 0;
  }
  */
  return 0;
}

void RepositoryMock::updateMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData)
{
  /*
  std::string commandString("UPDATE " + tableName_ + " SET metrics_data = '" + metricsData.dump() +
                            "' WHERE taskId = " + std::to_string(taskId.get()));
  sendCommand(commandString);
  */
}

void RepositoryMock::deleteMetricsData(measurementor::TaskId taskId)
{
  /*
  std::string commandString("DELETE " + tableName_ + "WHERE taskId = " + std::to_string(taskId.get()));
  sendCommand(commandString);
  */
}

void RepositoryMock::sendCommand(std::string command)
{
  /*
  std::string connectionString("postgresql://" + userName_ + ":" + password_ + "@" + hostName_ + ":" + port_ + "/" + databaseName_);
  logger_->log("[RepositoryMock] : connectionString : " + connectionString);
  logger_->log("[RepositoryMock] : command : " + command);
  pqxx::connection c{connectionString};
  pqxx::work txn{c};

  txn.exec(command);
  txn.commit();
  */
}

nlohmann::json RepositoryMock::sendQuery(measurementor::TaskId taskId)
{
  /*
  std::string connectionString("postgresql://" + userName_ + ":" + password_ + "@" + hostName_ + ":" + port_ + "/" + databaseName_);

  std::string queryString("SELECT metrics_data FROM " + tableName_ + " WHERE taskId = " + std::to_string(taskId.get()));

  logger_->log("[RepositoryMock] : connectionString : " + connectionString);
  logger_->log("[RepositoryMock] : command : " + queryString);
  pqxx::connection c{connectionString};
  pqxx::work txn{c};

  auto [metrics_data] = txn.query1<std::string>(queryString);
  txn.commit();
  return nlohmann::json::parse(metrics_data);
  */
  return nlohmann::json{};
}

}  // namespace repository