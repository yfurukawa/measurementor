/*!
 @file      ReworkRepository.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <sstream>
#include "ReworkRepository.h"

namespace repository
{

ReworkRepository::ReworkRepository(std::string userName, std::string password, std::string hostName, std::string port, std::string databaseName,
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

void ReworkRepository::registerReworkedTask(measurementor::TaskId taskId, measurementor::UpdatedAt reworkStartDate)
{
  std::string commandString("INSERT INTO " + tableName_ + "(taskId, reworkTimes) VALUES (" + std::to_string(taskId.get()) + ", 0)");
  sendCommand(commandString);
}

std::optional<measurementor::UpdatedAt> ReworkRepository::getStartDateOnInProgress(measurementor::TaskId taskId)
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
}

void ReworkRepository::deleteReworkedTask(measurementor::TaskId taskId)
{
  std::string commandString("DELETE FROM " + tableName_ + " WHERE taskId = " + std::to_string(taskId.get()));
  sendCommand(commandString);
}

void ReworkRepository::sendCommand(std::string command)
{
  std::string connectionString("postgresql://" + userName_ + ":" + password_ + "@" + hostName_ + ":" + port_ + "/" + databaseName_);
  logger_->log("[ReworkRepository] : connectionString : " + connectionString);
  logger_->log("[ReworkRepository] : command : " + command);
  pqxx::connection c{connectionString};
  pqxx::work txn{c};

  txn.exec(command);
  txn.commit();
}

void ReworkRepository::sendQuery(measurementor::TaskId taskId)
{
  std::string connectionString("postgresql://" + userName_ + ":" + password_ + "@" + hostName_ + ":" + port_ + "/" + databaseName_);

  std::string queryString("SELECT metrics_data FROM " + tableName_ + " WHERE taskId = " + std::to_string(taskId.get()));

  logger_->log("[ReworkRepository] : connectionString : " + connectionString);
  logger_->log("[ReworkRepository] : command : " + queryString);
  pqxx::connection c{connectionString};
  pqxx::work txn{c};

  auto [metrics_data] = txn.query1<std::string>(queryString);
  txn.commit();
  //return nlohmann::json::parse(metrics_data);
}

}  // namespace repository