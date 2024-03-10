/*!
 @file      Elasticsearch.h
 @brief     Elasticsearchとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <optional>
#include <string>
#include "Index.h"
#include "../../domain/IAnalyzer.h"
#include "DomainPrimitivesForElasticasearch.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     Elasticsearch
 @brief     Elasticsearchとインターフェースするクラス
 @note      本クラスは、Elasticsearchへデータと登録するためのクラスである。<br>
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
     @param[in]  apiKey Elasticsearchに送信する際に使用するAPIキー（6系のElasticsearchには不要）
     @param[in]  version 送信先Elasticsearchのバージョン
     @param[in]  index Elasticsearchへの登録に必要なインデックス
    */
    Elasticsearch( std::shared_ptr<ITcpClient> tcpClient, ApiKey apiKey, Version version, std::string index );

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
    std::shared_ptr<::ITcpClient> tcpClient_;    //!< Elasticsearchと通信するためのTCPクライアント
    ApiKey apiKey_;                              //!< Elasticsearchに接続する際に使用するBasic認証キー
    const Version version_;                      //!< Elasticsearchのバージョン
    std::unique_ptr<Index> index_;               //!< indexのドメインプリミティブ

    /*!
     @brief       計測データ登録
     @param[in]   登録データ
    */
    void sendRegisterMessage( const std::string& registoryString );

    std::optional<std::string> confirmServerResponse();
};

}
