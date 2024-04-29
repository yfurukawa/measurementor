/*!
 @file      IAnalyzer.h
 @brief     計測値を分析するシステムとインターフェースするクラスの抽象クラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     IAnalyzer
 @brief     計測値を分析するシステムとインターフェースするクラスの抽象クラス
 @note      本クラスは、メトリックスの測定値を分析するシステムとインターフェースするための抽象クラスである。<br>
 本クラスの具象クラスは、専用のファクトリクラスによりインスタンス化される。<br>
 現状、分析基盤としてelasticsearchを想定しており、それに合わせたインターフェースを規定している。
*/
class IAnalyzer
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  IAnalyzer() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~IAnalyzer() = default;

  /*!
   @brief      測定データ登録
   @param[in]  indexSuffix   elasticsearchのindexの一部となるサフィックス
   @param[in]  registerData  登録するデータ
  */
  virtual void registerMeasurementedData(const std::string& indexSuffix, const std::string& registerData) = 0;
};

}  // namespace measurementor
