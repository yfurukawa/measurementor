/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include "DomainPrimitivesForOpenProject.h"
#include "ITextFileWriter.h"

#include "../../domain/IPts.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;
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
     @param[in]  tcpClient OpenProjectと通信するためのTCPクライアント
     @param[in]  apiKey  サーバに接続するための認証キー
     std::string destination_;                    //!< 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
    unsigned int destinationPort_;               //!< 接続先ポート<br>通信ヘッダで使用する
    */
    explicit OpenProject( std::shared_ptr<::ITcpClient> tcpClient, ApiKey apiKey, std::string destination, unsigned int destinationPort );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~OpenProject() = default;

    /*!
     @brief  全てのアクティブプロジェクトを収集する
     @return アクティブプロジェクトのリスト（Projectの情報マップ（情報名、値）をリスト化したもの）
    */
    std::list<std::map<std::string, std::string>>  collectAllActiveProject() override;

    /*!
     @brief          指定されたプロジェクトに定義されているSprint情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectSprintInformation( const measurementor::ProjectId& projectId ) override;

    /*!
     @brief          指定されたプロジェクトに定義されているItemの情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         プロダクトバックログアイテムのリスト（PBIの情報マップ（情報名、値）をリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectItemInformation( const measurementor::ProjectId& projectId ) override;

    /*!
     @brief          指定されたプロジェクトに定義されているTaskの情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         タスクのリスト（タスクの情報マップ（情報名、値）をリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectTaskInformation( const measurementor::ProjectId& projectId ) override;

private:
    std::shared_ptr<::ITcpClient> tcpClient_;                 //!< OpenProjectと通信するためのTCPクライアント
    std::unique_ptr<::ITextFileWriter> previousDataWriter_;   //!< OpenProjectのサーバから取得したJsonオブジェクトをファイルに保存しておくためのWriter
    std::unique_ptr<JsonParser> jsonParser_;                  //!< Jsonオブジェクトのパーサ
    ApiKey apiKey_;                                           //!< OpenProjectに接続する際に使用するBasic認証キー
    std::string destination_;                                 //!< 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
    unsigned int destinationPort_;                            //!< 接続先ポート<br>通信ヘッダで使用する

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

    /*!
     @brief      OpenProjectサーバにクエリメッセージを送信する
     @param[in]  queryString  クエリストリング
     @return     サーバから受信したJsonオブジェクト
     @note       REST APIの通信に必要なヘッダ情報は本メソッド内で付加する
    */
    std::string sendQueryMessage(std::string queryString );

    /*!
     @brief      サーバから受信したJsonオブジェクトをファイルに保存する
     @param[in]  previousFaile  保存先のファイル名
     @param[in]  受信したJsonオブジェクト
    */
    void saveJsonObjectAsPreviousData( std::filesystem::path previousFile, std::string& receivedJson );
};

}
