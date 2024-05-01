/*!
 @file      IReworkRepositoryFactory.h
 @brief     手戻り回数の集計値やその元データを保持するRepositoryクラスのファクトリの抽象クラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IReworkRepository;

/*!
 @class     IReworkRepositoryFactory
 @brief     手戻り回数の集計値やその元データを保持するRepositoryクラスのファクトリの抽象クラス
*/
class IReworkRepositoryFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  IReworkRepositoryFactory() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~IReworkRepositoryFactory() = default;

  /*!
  @brief      ReworkRepositoryFactoryインスタンスを生成する
  @return     ReworkRepositoryFactoryインスタンス
  @note       本メソッドは、各具象クラス内でRepositoryFactoryクラスのメソッドとして実装される。
  */
  static IReworkRepositoryFactory* getInstance();

  /*!
  @brief      ReworkRepositoryとインターフェースするクラスのインスタンスを生成する
  @return     ReworkRepositoryとインターフェースするクラスのインスタンス
  */
  virtual IReworkRepository* createRepository() = 0;

protected:
  std::mutex ReworkRepositoryMtx_;  //!< インスタンス生成処理保護用mutex
};

}  // namespace measurementor
