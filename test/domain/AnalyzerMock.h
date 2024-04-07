/*!
 @file      AnalyzerMock.h
 @brief     AnalyzerMockとインターフェースするクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <optional>
#include <string>
#include "../../src/analyzer/elasticsearch/Index.h"
#include "../../src/domain/IAnalyzer.h"
#include "../../src/analyzer/elasticsearch/DomainPrimitivesForElasticasearch.h"
#include "Logger.h"
#include "LoggerFactory.h"

// ---------< forward declaration (Global) >-------------
class ITcpClient;

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     AnalyzerMock
 @brief     AnalyzerMockとインターフェースするクラス
 @note      本クラスは、AnalyzerMockへデータと登録するためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class AnalyzerMock final : public measurementor::IAnalyzer
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  AnalyzerMock() = default;

  /*!
   @brief  コンストラクタ
   @param[in]  tcpClient AnalyzerMockと通信するためのTCPクライアント
   @param[in]  apiKey AnalyzerMockに送信する際に使用するAPIキー（6系のAnalyzerMockには不要）
   @param[in]  version 送信先AnalyzerMockのバージョン
   @param[in]  index AnalyzerMockへの登録に必要なインデックス
   @param[in]  destination_ 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
   @param[in]  destinationPort_ 接続先ポート<br>通信ヘッダで使用する
  */
//  AnalyzerMock(std::shared_ptr<ITcpClient> tcpClient, ApiKey apiKey, Version version, std::unique_ptr<Index> index,
//                std::string destination, unsigned int destinationPort);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~AnalyzerMock() = default;

  /*!
   @brief      測定データ登録
   @param[in]  登録するデータ
  */
  void registerMeasurementedData(const std::string& registerData) override;

private:
/*
  std::shared_ptr<::ITcpClient> tcpClient_;  //!< AnalyzerMockと通信するためのTCPクライアント
  ApiKey apiKey_;                            //!< AnalyzerMockに接続する際に使用するBasic認証キー
  const Version version_;                    //!< AnalyzerMockのバージョン
  std::unique_ptr<Index> index_;             //!< indexのドメインプリミティブ
  std::string destination_;       //!< 接続先サーバ（IPアドレスまたはホスト名）<br>通信ヘッダで使用する
  unsigned int destinationPort_;  //!< 接続先ポート<br>通信ヘッダで使用する
  AbstLogger::LoggerFactory* loggerFactory_;  //!< Logger Factory
  AbstLogger::Logger* logger_;  //!< Logger
*/
  /*!
   @brief       計測データ登録
   @param[in]   登録データ
  */
  void sendRegisterMessage(const std::string& registoryString);

  std::optional<std::string> confirmServerResponse();
};

}  // namespace analyzer
