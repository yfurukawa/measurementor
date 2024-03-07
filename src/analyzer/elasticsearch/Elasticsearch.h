/*!
 @file      Elasticsearch.h
 @brief     Elasticsearchとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include "../../domain/IAnalyzer.h"
#include "DomainPrimitives.h"

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
    Elasticsearch( std::unique_ptr<TcpClient> tcpClient, ApiKey apiKey );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Elasticsearch() = default;

private:
    std::unique_ptr<::TcpClient> tcpClient_;         //!< Elasticsearchと通信するためのTCPクライアント
    ApiKey apiKey_;                                  //!< Elasticsearchに接続する際に使用するBasic認証キー

    std::string sendQueryMessage(std::string queryString );

};

}
