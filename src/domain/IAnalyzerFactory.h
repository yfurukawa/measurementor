/*!
 @file      IAnalyzerFactory.h
 @brief     計測値を分析するシステムとインターフェースするクラスのファクトリの抽象クラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IAnalyzer;

/*!
 @class     IAnalyzerFactory
 @brief     計測値を分析するシステムとインターフェースするクラスのファクトリの抽象クラス
*/
class IAnalyzerFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  IAnalyzerFactory() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~IAnalyzerFactory() = default;

  /*!
  @brief      IAnalyzerFactoryインスタンスを生成する
  @return     IAnalyzerFactoryインスタンス
  @note       本メソッドは、各具象クラス内でIAnalyzerFactoryクラスのメソッドとして実装される。
  */
  static IAnalyzerFactory* getInstance();

  /*!
  @brief      IAnalyzerとインターフェースするクラスのインスタンスを生成する
  @return     IAnalyzerとインターフェースするクラスのインスタンス
  */
  virtual IAnalyzer* createIAnalyzer() = 0;

protected:
  std::mutex IAnalyzerMtx_;  //!< インスタンス生成処理保護用mutex
};

}  // namespace measurementor
