/*!
 @file      Repository.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "../../domain/domainPrimitives/MeasurementPrimitives.h"
#include "ITextFileWriter.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "../../domain/IRepository.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;
class TextFileWriter;

// --------------< namespace >---------------------------
namespace repository
{

// ---------< forward declaration >----------------------

/*!
 @class     Repository
 @brief     Repositoryとインターフェースするクラス
 @note      本クラスは、Repositoryからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class Repository final : public measurementor::IRepository
{
  /*!
   @brief  デフォルトコンストラクタ
  */
  Repository() = delete;

public:
  /*!
   @brief  コンストラクタ
   @param[in]  tcpClient Repositoryと通信するためのTCPクライアント
   @param[in]  destination 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
   @param[in]  destinationPort 接続先ポート<br>通信ヘッダで使用する
  */
  explicit Repository(std::shared_ptr<::ITcpClient> tcpClient, std::string destination, unsigned int destinationPort);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~Repository() = default;

  /*!
   @brief     タスクのメトリックスを登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] metricsData json形式にしたメトリックスデータ
  */
  void registerMetricsData(TaskId taskId, nlohmann::json metricsData) override;

  /*!
   @brief     タスクがIn Progress状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    nlohmann::json メトリックスデータ
  */
  nlohmann::json getInProgressStartedDate(measurementor::TaskId taskId) override;

private:
  std::shared_ptr<::ITcpClient> tcpClient_;  //!< Repositoryと通信するためのTCPクライアント
  std::string destination_;       //!< 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
  unsigned int destinationPort_;  //!< 接続先ポート<br>通信ヘッダで使用する
  std::unique_ptr<::ITextFileWriter>
    previousDataWriter_;  //!< Repositoryのサーバから取得したJsonオブジェクトをファイルに保存しておくためのWriter
    AbstLogger::LoggerFactory* loggerFactory_;  //!< Logger Factory
  AbstLogger::Logger* logger_;  //!< Logger

};

}  // namespace repository
