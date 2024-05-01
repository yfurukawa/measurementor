/*!
 @file      ReworkRepository.h
 @brief     メトリックスの計算値やその元データを保持するReworkRepositoryクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include <pqxx/pqxx>
#include <string>
#include "../../domain/domainPrimitives/MeasurementPrimitives.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "../../domain/IReworkRepository.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;
class TextFileWriter;

// --------------< namespace >---------------------------
namespace repository
{

// ---------< forward declaration >----------------------

/*!
 @class     ReworkRepository
 @brief     ReworkRepositoryとインターフェースするクラス
 @note      本クラスは、ReworkRepositoryからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class ReworkRepository final : public measurementor::IReworkRepository
{
  /*!
   @brief  デフォルトコンストラクタ
  */
  ReworkRepository() = delete;

public:

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
  ReworkRepository(std::string userName, std::string password, std::string hostName, std::string port, std::string databaseName,
             std::string tableName);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~ReworkRepository() = default;

  /*!
   @brief     手戻りがあったタスクを新規登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] reworkStartDate  手戻りにより再びIn Progressに戻った日時
  */
  void registerReworkedTask(measurementor::TaskId taskId, measurementor::UpdatedAt reworkStartDate) override;

  /*!
   @brief     タスクがIn Progress状態に戻った日時を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    In Progress状態に移行した日時
   @note      対象タスクの日時が登録されていない場合、std::nulloptが返される
  */
  std::optional<measurementor::UpdatedAt> getStartDateOnInProgress(measurementor::TaskId taskId) override;

  /*!
   @brief     タスクがReview状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    Review状態に移行した日時
   @note      対象タスクの日時が登録されていない場合、std::nulloptが返される
  */
  std::optional<measurementor::UpdatedAt> getStarDateOnReview(measurementor::TaskId taskId) override;

  /*!
   @brief     タスクのメトリックスを削除する
   @param[in] taskId 削除対象タスクのID
  */
  void deleteReworkedTask(measurementor::TaskId taskId) override;

private:
  std::string userName_;                      //!< DBサーバに接続するユーザ名
  std::string password_;                      //!< パスワード
  std::string hostName_;                      //!< DBサーバのホスト名又はIPアドレス
  std::string port_;                          //!< DBサーバの待受ポート
  std::string databaseName_;                  //!< メトリックスを保存するデータベース名
  std::string tableName_;                     //!< メトリックスを保存するテーブル名
  AbstLogger::LoggerFactory* loggerFactory_;  //!< Logger Factory
  AbstLogger::Logger* logger_;                //!< Logger

  /*!
   @brief DBサーバにコマンドを送信する
   @param[in]  command  DBサーバに送信するSQLコマンド
  */
  void sendCommand(std::string command);

  /*!
   @brief DBサーバにクエリを送信する
   @param[in]  taskId クエリ対象のTaskID
   @return     クエリ結果
  */
  void sendQuery(measurementor::TaskId taskId);
};

}  // namespace repository
