/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "DomainPrimitivesForOpenProject.h"
#include "ITextFileWriter.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "../../domain/IPts.h"

// ---------< forward declaration (Global) >-------------
//class ITcpClient;
class TextFileWriter;

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------
class JsonParser;

/*!
 @class     OpenProject
 @brief     OpenProjectとインターフェースするクラス
 @note      本クラスは、OpenProjectからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class OpenProject final : public measurementor::IPts
{
  /*!
   @brief  デフォルトコンストラクタ
  */
  OpenProject() = delete;

public:
  /*!
   @brief  コンストラクタ
   @param[in]  apiKey  サーバに接続するための認証キー
   @param[in]  destination 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
   @param[in]  destinationPort 接続先ポート<br>通信ヘッダで使用する
  */
  explicit OpenProject(ApiKey apiKey, std::string destination, unsigned int destinationPort);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~OpenProject() = default;

  /*!
   @brief  全てのアクティブプロジェクトを収集する
   @return アクティブプロジェクトのリスト（Projectの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectAllActiveProject() override;

  /*!
   @brief          指定されたプロジェクトに定義されているSprint情報を収集する
   @param[in]      projectId  収集したいプロジェクトのID
   @return         スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectSprintInformation(const measurementor::ProjectId& projectId) override;

  /*!
   @brief          指定されたプロジェクトに定義されているItemの情報を収集する
   @param[in]      projectId  収集したいプロジェクトのID
   @return         プロダクトバックログアイテムのリスト（PBIの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectItemInformation(const measurementor::ProjectId& projectId) override;

  /*!
   @brief          指定されたプロジェクトに定義されているTaskの情報を収集する
   @param[in]      projectId  収集したいプロジェクトのID
   @return         タスクのリスト（タスクの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectTaskInformation(const measurementor::ProjectId& projectId) override;

private:
  ApiKey apiKey_;                            //!< OpenProjectに接続する際に使用するBasic認証キー
  std::string destination_;       //!< 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
  unsigned int destinationPort_;  //!< 接続先ポート<br>通信ヘッダで使用する
  std::unique_ptr<::ITextFileWriter>
    previousDataWriter_;  //!< OpenProjectのサーバから取得したJsonオブジェクトをファイルに保存しておくためのWriter
  std::unique_ptr<JsonParser> jsonParser_;  //!< Jsonオブジェクトのパーサ
  AbstLogger::LoggerFactory* loggerFactory_;  //!< Logger Factory
  AbstLogger::Logger* logger_;  //!< Logger

  /*!
   @brief      OpenProjectサーバにクエリメッセージを送信する
   @param[in]  queryString  クエリストリング
   @return     サーバから受信したJsonオブジェクト
   @note       REST APIの通信に必要なヘッダ情報は本メソッド内で付加する
  */
  std::string sendQueryMessage(std::string queryString);

  /*!
   @brief      サーバから受信したJsonオブジェクトをファイルに保存する
   @param[in]  previousFile  保存先のファイル名
   @param[in]  receivedJson  受信したJsonオブジェクト
  */
  void saveJsonObjectAsPreviousData(std::filesystem::path previousFile, const std::string& receivedJson);

  /*!
   @brief     OpenProjectから取得したJsonデータの一時ファイルが有効になるまで待機する
  */
  void waitToAvailableTempolalyFile();
};

}  // namespace pts
