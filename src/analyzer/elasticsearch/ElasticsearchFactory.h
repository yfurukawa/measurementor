/*!
 @file      ElasticsearchFactory.h
 @brief     Elasticsearchとインターフェースするクラスのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "ConfFileParser.h"
#include "DomainPrimitives.h"
#include "Elasticsearch.h"
#include "../../domain/IAnalyzerFactory.h"
#include "Hostname.h"
#include "IPv4.h"
#include "Port.h"
#include "TcpClient.h"

#include <iostream>

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     ElasticsearchFactory
 @brief     Elasticsearchとインターフェースするクラスのファクトリクラス
 @note      本クラスはElasticsearchとインターフェースするクラスのファクトリクラスである。ElasticsearchクラスとでAbstruct Factoryパターンを形成している。
 また、Elasticsearchクラスは、TcpClientを必要としているためそのインスタンスも生成している。
*/
class ElasticsearchFactory final : public measurementor::IAnalyzerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ElasticsearchFactory()
        : analyzer_(nullptr)
    {
        std::filesystem::path confFile("/usr/local/etc/measurementor/elasticsearch.conf");   // TODO pathは別途設定できると良い
        confFileParser_ = std::make_unique<ConfFileParser>( confFile );
        ElasticsearchFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ElasticsearchFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return ElasticsearchFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToSyslogLoggerインスタンス
    */
    measurementor::IAnalyzer* createIAnalyzer() override
    {
        if( !analyzer_ ) {
            std::lock_guard<std::mutex> lock(IAnalyzerMtx_);
            if( !analyzer_ ) {
                auto result = confFileParser_->parseFile();
                if( !result )
                {
                    perror(" Can not read Elasticsearch.conf");
                    exit(1);
                }
                else
                {
                    setting_ = result.value();
                }
                IPv4 ip( setting_["IP"] );
                Port port( std::stoi( setting_["Port"] ) );
                ApiKey apiKey( setting_["apikey"] );
                Version version( setting_["version"] );
                analyzer_ = dynamic_cast<measurementor::IAnalyzer*>( new Elasticsearch( std::make_unique<::TcpClient>( ip, port ), apiKey, version ) );
            }
        }
        return analyzer_;
    }

private:
    measurementor::IAnalyzer* analyzer_;                   //!< Elasticsearchとインターフェースするクラス
    static bool destroyed_;                                //!< インスタンスの破棄ステータス
    std::unique_ptr<ConfFileParser> confFileParser_;       //!< confファイルのパーサ
    std::map<std::string, std::string> setting_;           //!< confファイルから読み込んだElasticsearchサーバに関する設定（ホスト名、IPアドレス、接続先ポート、API Key）
};

}
