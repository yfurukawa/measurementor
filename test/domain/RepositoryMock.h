/*!
 @file      RepositoryMock.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryMockクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include <pqxx/pqxx>
#include <string>
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "../../src/domain/IRepository.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;
class TextFileWriter;

// --------------< namespace >---------------------------
namespace repository
{

// ---------< forward declaration >----------------------

/*!
 @class     RepositoryMock
 @brief     RepositoryMockとインターフェースするクラス
 @note      本クラスは、RepositoryMockからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class RepositoryMock final : public measurementor::IRepository
{
public:

  /*!
   @brief  デフォルトコンストラクタ
  */
  RepositoryMock();

  /*!
   @brief  コンストラクタ
   @param[in]  userName  データベースに接続するユーザ
   @param[in]  password  ユーザのパスワード
   @param[in]  hostName  データベースサーバ名
   @param[in]  port  データベースサーバの待受ポート
   @param[in]  databaseName  メトリックスデータを保存するデータベース名
   @param[in]  tableName  メトリックスデータを保存するテーブル名
   @attention  データベース名は、接続文字列に含むことを想定しているため、正確性のチェックはしていない。更に、IPアドレスでも許容される。
  */
//  RepositoryMock(std::string userName, std::string password, std::string hostName, std::string port, std::string databaseName,
//             std::string tableName);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~RepositoryMock() = default;

  /*!
   @brief     タスクのメトリックスを登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] metricsData json形式にしたメトリックスデータ
  */
  void registerMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData) override;

  /*!
   @brief     タスクがIn Progress状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID
   @return    nlohmann::json メトリックスデータ
  */
  std::optional<measurementor::UpdatedAt> getStarDateOnInProgress(measurementor::TaskId taskId) override;

  /*!
     @brief     タスクがReview状態に移行した日付を取得する
     @param[in] taskId 取得対象タスクのID
     @return    nlohmann::json メトリックスデータ
    */
  std::optional<measurementor::UpdatedAt> getStarDateOnReview(measurementor::TaskId taskId) override;

  /*!
     @brief     タスクがComplete状態に移行した日付を取得する
     @param[in] taskId 取得対象タスクのID
     @return    nlohmann::json メトリックスデータ
    */
  std::optional<measurementor::UpdatedAt> getStarDateOnClose(measurementor::TaskId taskId) override;

  /*!
   @brief     InProgressのDurationを取得する
   @param[in] taskId 取得対象タスクのID 
   @return    時間[H]
  */
  double getInProgressDuration(measurementor::TaskId taskId) override;

  /*!
   @brief     タスクのメトリックスを更新する
   @param[in] taskId 更新対象タスクのID
   @param[in] metricsData json形式にしたメトリックスデータ
  */
  void updateMetricsData(measurementor::TaskId taskId, nlohmann::json metricsData) override;

  /*!
   @brief     タスクのメトリックスを削除する
   @param[in] taskId 削除対象タスクのID
  */
  void deleteMetricsData(measurementor::TaskId taskId) override;

  void setStarDateOnInProgress(std::string date);
  void setStarDateOnReview(std::string date);
  void setInProgressDuration(double duration);
  std::string getMetricsData();
  void clear();
  
private:
  std::string starDateOnInProgress_;
  std::string starDateOnReview_;
  double inProgressDuration_;
  nlohmann::json metricsData_;

  /*!
   @brief DBサーバにコマンドを送信する
   @param[in]  command  DBサーバに送信するSQLコマンド
  */
  void sendCommand(std::string command);

  /*!
   @brief DBサーバにクエリを送信する
   @param[in]  query  DBサーバに送信するSQLクエリ
   @return     クエリ結果
  */
  nlohmann::json sendQuery(measurementor::TaskId taskId);
};

}  // namespace repository
