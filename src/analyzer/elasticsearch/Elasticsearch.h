/*!
 @file      Elasticsearch.h
 @brief     Elasticsearchとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <optional>
#include <string>
#include "../../domain/IAnalyzer.h"
#include "DomainPrimitivesForElasticasearch.h"

// ---------< forward declaration (Global) >-------------
class TcpClient;
class TextFileWriter;

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     Elasticsearch
 @brief     Elasticsearchとインターフェースするクラス
 @note      本クラスは、Elasticsearchからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class Elasticsearch final : public measurementor::IAnalyzer
{
    /*!
     @brief  デフォルトコンストラクタ
    */
    Elasticsearch() = delete;
public:
    /*!
     @brief  コンストラクタ
     @param[in]  tcpClient Elasticsearchと通信するためのTCPクライアント
    */
    Elasticsearch( std::unique_ptr<TcpClient> tcpClient, ApiKey apiKey, Version version );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Elasticsearch() = default;

    /*!
     @brief      測定データ登録
     @param[in]  登録するデータ
    */
    void registerMeasurementedData( const std::string& registerData ) override;

private:
    std::unique_ptr<::TcpClient> tcpClient_;    //!< Elasticsearchと通信するためのTCPクライアント
    ApiKey apiKey_;                             //!< Elasticsearchに接続する際に使用するBasic認証キー
    const Version version_;                     //!< Elasticsearchのバージョン

    /*!
     @brief       計測データ登録
     @param[in]   登録データ
    */
    void sendRegisterMessage( const std::string& registoryString );

    std::optional<std::string> confirmServerResponse();
};

}
