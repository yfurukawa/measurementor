/*!
 @file      AnalyzerMockFactory.h
 @brief     AnalyzerMockとインターフェースするクラスのファクトリクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "ConfFileParser.h"
#include "../../src/analyzer/elasticsearch/DomainPrimitivesForElasticasearch.h"
#include "AnalyzerMock.h"
#include "Hostname.h"
#include "../../src/analyzer/elasticsearch/Index.h"
#include "IPv4.h"
#include "Port.h"
#include "TcpClient.h"
#include "../../src/domain/IAnalyzerFactory.h"

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     AnalyzerMockFactory
 @brief     AnalyzerMockとインターフェースするクラスのファクトリクラス
 @note      本クラスはAnalyzerMockとインターフェースするクラスのファクトリクラスである。AnalyzerMockクラスとでAbstruct
 Factoryパターンを形成している。 また、AnalyzerMockクラスは、TcpClientを必要としているためそのインスタンスも生成している。
*/
class AnalyzerMockFactory final : public measurementor::IAnalyzerFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  AnalyzerMockFactory() : analyzer_(nullptr)
  {
    /*
    std::filesystem::path confFile("/usr/local/etc/measurementor/elasticsearch.conf");  // TODO(yfurukawa) pathは別途設定できると良い
    confFileParser_ = std::make_unique<ConfFileParser>(confFile);
    */
    AnalyzerMockFactory::destroyed_ = false;
  }

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~AnalyzerMockFactory();

  /*!
  @brief      インスタンスの破棄ステータスを返す
  @return     true : インスタンス破棄済み
  */
  static const bool isDestroyed() { return AnalyzerMockFactory::destroyed_; }

  /*!
  @brief      分析システムとインターフェースするクラスインスタンスを生成する
  @return     AnalyzerMockクラスのインスタンス
  */
  measurementor::IAnalyzer* createIAnalyzer() override
  {
    if (!analyzer_)
    {
      std::lock_guard<std::mutex> lock(IAnalyzerMtx_);
      if (!analyzer_)
      {
        /*
        auto result = confFileParser_->parseFile();
        if (!result)
        {
          perror(" Can not read elasticsearch.conf");
          exit(1);
        }
        else
        {
          setting_ = result.value();
        }
        // confファイルにIPが設定されていればそれを使う
        IPv4 ip((setting_.find("IP") != end(setting_)) ? setting_["IP"] : "0.0.0.0");
        // confファイルにHostが設定されていればそれを使う
        Hostname host((setting_.find("Host") != end(setting_)) ? setting_["Host"] : "");
        Port port(std::stoi(setting_["Port"]));
        ApiKey apiKey(setting_["apikey"]);
        Version version(setting_["version"]);
        std::unique_ptr<Index> index(std::make_unique<Index>(setting_["index"]));
        if (ip != "0.0.0.0")
        {
          analyzer_ = dynamic_cast<measurementor::IAnalyzer*>(
            new AnalyzerMock(std::make_shared<::TcpClient>(ip, port), apiKey, version, std::move(index), ip.get(), port.get()));
        }
        else
        {
          analyzer_ = dynamic_cast<measurementor::IAnalyzer*>(
            new AnalyzerMock(std::make_shared<::TcpClient>(host, port), apiKey, version, std::move(index), host.get(), port.get()));
        }
        */
        analyzer_ = dynamic_cast<measurementor::IAnalyzer*>(new AnalyzerMock());
      }
    }
    return analyzer_;
  }

private:
  measurementor::IAnalyzer* analyzer_;              //!< AnalyzerMockとインターフェースするクラス
  static bool destroyed_;                           //!< インスタンスの破棄ステータス
  std::unique_ptr<ConfFileParser> confFileParser_;  //!< confファイルのパーサ
  std::map<std::string, std::string>
    setting_;  //!< confファイルから読み込んだAnalyzerMockサーバに関する設定（ホスト名、IPアドレス、接続先ポート、API Key）
};

}  // namespace analyzer
