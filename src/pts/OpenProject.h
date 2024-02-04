/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include "../domain/Pts.h"

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
    explicit OpenProject( std::unique_ptr<TcpClient> tcpClient );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~OpenProject() = default;

    /*!
     @brief  全てのアクティブプロジェクトを収集する
     @return アクティブプロジェクトのリスト
    */
    void collectAllActiveProject( std::map<unsigned int, std::shared_ptr<measurementor::Project>>& projectList ) override;

private:
    std::unique_ptr<::TcpClient> tcpClient_; //!< OpenProjectと通信するためのTCPクライアント
    std::unique_ptr<JsonParser> jsonParser_; //!< Json文字列のパーサ

    /*!
     @brief  受信データからJSONストリングを抽出する
     @return JSONストリング
    */
    std::string extractJsonFron();

    /*!
     @brief      受信データがJSONストリングが判定する
     @param[in]  received 判定対象とする受信データ
     @return     true : JSONストリング
    */
    bool isJsonString( std::string received );
};

}
