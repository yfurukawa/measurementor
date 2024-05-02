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

std::optional<measurementor::ReworkTimes> ReworkRepository::getReworkTimes(measurementor::TaskId taskId)
{
  try
  {
    return sendQuery(taskId);
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
    std::string exceptionString(e.what());
    if (exceptionString == "Expected 1 row(s) of data from query , got 0.")
    {
      // 対象Taskの手戻り回数が登録されていない場合、上記のメッセージを伴う例外がスローされる
      // この場合は、想定されている例外（初めての手戻りだった）なので、単純にnulloptを返して
      // データが未登録であったことを示す
      return std::nullopt;
    }
    else
    {
      std::stringstream errorStream;
      errorStream << "[Repositoruy][getStarDateOnInProgress] : Error: " << e.what();
      logger_->log(errorStream.str());
      return std::nullopt;
    }
  }
}

void ReworkRepository::registerReworkedTask(measurementor::TaskId taskId, measurementor::UpdatedAt reworkStartDate)
{
  std::string commandString("INSERT INTO " + tableName_ + "(taskId, reworkTimes) VALUES (" + std::to_string(taskId.get()) + ", 1)");
  sendCommand(commandString);
}

void ReworkRepository::storeNewReworkTimes(measurementor::TaskId taskId, measurementor::ReworkTimes newReworkTimes)
{
  std::string commandString("UPDATE " + tableName_ + " SET reworkTimes = '" + std::to_string(newReworkTimes.get()) +
                            "' WHERE taskId = " + std::to_string(taskId.get()));
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
  return std::nullopt;
}

std::optional<measurementor::UpdatedAt> ReworkRepository::getStartDateOnReview(measurementor::TaskId taskId)
{
  return std::nullopt;
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

measurementor::ReworkTimes ReworkRepository::sendQuery(measurementor::TaskId taskId)
{
  std::string connectionString("postgresql://" + userName_ + ":" + password_ + "@" + hostName_ + ":" + port_ + "/" + databaseName_);

  std::string queryString("SELECT reworkTimes FROM " + tableName_ + " WHERE taskId = " + std::to_string(taskId.get()));

  logger_->log("[ReworkRepository] : connectionString : " + connectionString);
  logger_->log("[ReworkRepository] : command : " + queryString);
  pqxx::connection c{connectionString};
  pqxx::work txn{c};

  auto [reworkTimes] = txn.query1<std::uint_fast16_t>(queryString);
  txn.commit();

  return measurementor::ReworkTimes(reworkTimes);
}

}  // namespace repository