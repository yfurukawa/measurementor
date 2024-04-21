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
   @brief  デフォルトデストラクタ
  */
  virtual ~AnalyzerMock() = default;

  /*!
   @brief      測定データ登録
   @param[in]  登録するデータ
  */
  void registerMeasurementedData(const std::string& indexSuffix, const std::string& registerData) override;

private:
  /*!
   @brief       計測データ登録
   @param[in]   登録データ
  */
  void sendRegisterMessage(const std::string& registoryString);

  std::optional<std::string> confirmServerResponse();
};

}  // namespace analyzer
