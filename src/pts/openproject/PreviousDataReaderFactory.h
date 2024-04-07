/*!
 @file      PreviousDataReaderFactory.h
 @brief     PreviousDataReaderとインターフェースするクラスのファクトリクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "TextFileReader.h"
#include "../../domain/IPreviousDataReaderFactory.h"
#include "PreviousDataReader.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     PreviousDataReaderFactory
 @brief     PreviousDataを読み込むクラスのファクトリクラス
 @note      本クラスはPreviousDataを読み込むクラスのファクトリクラスである。PreviousDataReaderクラスとでAbstruct
 Factoryパターンを形成している。 また、PreviousDataReaderクラスは、TextFileReaderを必要としているためそのインスタンスも生成している。
*/
class PreviousDataReaderFactory final : public measurementor::IPreviousDataReaderFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  PreviousDataReaderFactory() : previousDataReader_(nullptr) { PreviousDataReaderFactory::destroyed_ = false; }

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~PreviousDataReaderFactory();

  /*!
  @brief      インスタンスの破棄ステータスを返す
  @return     true : インスタンス破棄済み
  */
  static const bool isDestroyed() { return PreviousDataReaderFactory::destroyed_; }

  /*!
  @brief      PreviousDataReaderインスタンスを生成する
  @return     PreviousDataReaderインスタンス
  */
  measurementor::IPreviousDataReader* createPreviousDataReader() override
  {
    if (!previousDataReader_)
    {
      std::lock_guard<std::mutex> lock(previousDataReaderMtx_);
      if (!previousDataReader_)
      {
        previousDataReader_ = dynamic_cast<measurementor::IPreviousDataReader*>(new PreviousDataReader(std::make_unique<::TextFileReader>()));
      }
    }
    return previousDataReader_;
  }

private:
  measurementor::IPreviousDataReader* previousDataReader_;  //!< PreviousDataReaderとインターフェースするクラス
  static bool destroyed_;                                   //!< インスタンスの破棄ステータス
};

}  // namespace pts
