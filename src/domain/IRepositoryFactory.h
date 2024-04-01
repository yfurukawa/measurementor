/*!
 @file      IRepositoryFactory.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスのファクトリの抽象クラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IRepository;

/*!
 @class     IRepositoryFactory
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスのファクトリの抽象クラス
*/
class IRepositoryFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  IRepositoryFactory() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~IRepositoryFactory() = default;

  /*!
  @brief      RepositoryFactoryインスタンスを生成する
  @return     RepositoryFactoryインスタンス
  @note       本メソッドは、各具象クラス内でRepositoryFactoryクラスのメソッドとして実装される。
  */
  static IRepositoryFactory* getInstance();

  /*!
  @brief      Repositoryとインターフェースするクラスのインスタンスを生成する
  @return     Repositoryとインターフェースするクラスのインスタンス
  */
  virtual IRepository* createRepository() = 0;

protected:
  std::mutex RepositoryMtx_;  //!< インスタンス生成処理保護用mutex
};

}  // namespace measurementor
