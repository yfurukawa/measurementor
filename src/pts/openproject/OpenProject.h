/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
//#include <map>
//#include <memory>
//#include <string>
#include "DomainPrimitives.h"
#include "../../domain/Pts.h"

// ---------< forward declaration (Global) >-------------
class TcpClient;

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
class OpenProject final : public measurementor::Pts
{
    /*!
     @brief  デフォルトコンストラクタ
    */
    OpenProject() = delete;
public:
    /*!
     @brief  コンストラクタ
     @param[in]  tcpClient OpenProjectと通信するためのTCPクライアント
    */
    explicit OpenProject( std::unique_ptr<TcpClient> tcpClient, ApiKey apiKey );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~OpenProject() = default;

    /*!
     @brief  全てのアクティブプロジェクトを収集する
     @return アクティブプロジェクトのリスト
    */
    std::list<std::map<std::string, std::string>>  collectAllActiveProject() override;

    /*!
     @brief          指定されたプロジェクトに定義されているSprint情報を収集する
     @param[in,out]  project 収集したいプロジェクト
    */
    std::list<std::map<std::string, std::string>> collectSprintInformationOf( std::shared_ptr<measurementor::Project>& project ) override;

    /*!
     @brief          指定されたプロジェクトに定義されているItemの情報を収集する
     @param[in,out]  project 収集したいプロジェクト
    */
    std::list<std::map<std::string, std::string>> collectItemInformation( std::shared_ptr<measurementor::Project>& project ) override;

    /*!
     @brief          指定されたプロジェクトに定義されているTaskの情報を収集する
     @param[in,out]  project 収集したいプロジェクト
    */
    std::list<std::map<std::string, std::string>> collectTaskInformation( std::shared_ptr<measurementor::Project>& project ) override;

private:
    std::unique_ptr<::TcpClient> tcpClient_;         //!< OpenProjectと通信するためのTCPクライアント
    std::unique_ptr<JsonParser> jsonParser_;         //!< Json文字列のパーサ
    ApiKey apiKey_;                                  //!< OpenProjectに接続する際に使用するBasic認証キー

    /*!
     @brief  受信データからJSONストリングを抽出する
     @return JSONストリング
    */
    std::string extractJsonFrom();

    /*!
     @brief      受信データがJSONストリングが判定する
     @param[in]  received 判定対象とする受信データ
     @return     true : JSONストリング
    */
    bool isJsonString( std::string received );

    std::string sendQueryMessage(std::string queryString );
};

}
