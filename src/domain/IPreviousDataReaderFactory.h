/*!
 @file      IPreviousDataReaderFactory.h
 @brief     PreviousDataを読み込むクラスのファクトリの抽象クラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IPreviousDataReader;

/*!
 @class     IPreviousDataReaderFactory
 @brief     PreviousDataを読み込むクラスのファクトリの抽象クラス
*/
class IPreviousDataReaderFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  IPreviousDataReaderFactory() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~IPreviousDataReaderFactory() = default;

  /*!
  @brief      PreviousDataFactoryインスタンスを生成する
  @return     PreviousDataFactoryyインスタンス
  @note       本メソッドは、各具象クラス内でPreviousDataFactoryクラスのメソッドとして実装される。
  */
  static IPreviousDataReaderFactory* getInstance();

  /*!
  @brief      PreviousDataを読み込むクラスのインスタンスを生成する
  @return     PreviousDataを読み込むクラスのインスタンス
  */
  virtual IPreviousDataReader* createPreviousDataReader() = 0;

protected:
  std::mutex previousDataReaderMtx_;  //!< インスタンス生成処理保護用mutex
};

}  // namespace measurementor
