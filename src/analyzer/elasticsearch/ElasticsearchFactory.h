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
#include "DomainPrimitivesForElasticasearch.h"
#include "Elasticsearch.h"
#include "Hostname.h"
#include "Index.h"
#include "IPv4.h"
#include "Port.h"
#include "TcpClient.h"
#include "../../domain/IAnalyzerFactory.h"

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
    @brief      分析システムとインターフェースするクラスインスタンスを生成する
    @return     Elasticsearchクラスのインスタンス
    */
    measurementor::IAnalyzer* createIAnalyzer() override
    {
        if( !analyzer_ ) {
            std::lock_guard<std::mutex> lock(IAnalyzerMtx_);
            if( !analyzer_ ) {
                auto result = confFileParser_->parseFile();
                if( !result )
                {
                    perror(" Can not read elasticsearch.conf");
                    exit(1);
                }
                else
                {
                    setting_ = result.value();
                }
                // confファイルにIPが設定されていればそれを使う
                IPv4 ip( ( setting_.find("IP") != end( setting_ ) ) ? setting_["IP"] : "0.0.0.0" );
                // confファイルにHostが設定されていればそれを使う
                Hostname host( ( setting_.find("Host") != end( setting_ ) ) ? setting_["Host"] : "" );
                Port port( std::stoi( setting_["Port"] ) );
                ApiKey apiKey( setting_["apikey"] );
                Version version( setting_["version"] );
                std::unique_ptr<Index> index( std::make_unique<Index>( setting_["index"] ) );
                if( ip != "0.0.0.0" )
                {
                    analyzer_ = dynamic_cast<measurementor::IAnalyzer*>( new Elasticsearch( std::make_shared<::TcpClient>( ip, port ), apiKey, version, std::move( index ), ip.get(), port.get() ) );
                }
                else{
                    analyzer_ = dynamic_cast<measurementor::IAnalyzer*>( new Elasticsearch( std::make_shared<::TcpClient>( host, port ), apiKey, version, std::move( index ), host.get(), port.get() ) );
                }
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
