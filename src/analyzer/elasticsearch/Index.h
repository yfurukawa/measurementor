/*!
 @file      Index.h
 @brief     Elasticsearchの登録用Indexを調整する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------

/*!
 @class     Index
 @brief     Elasticsearchの登録用Indexを調整する
 @note      本クラスは、Elasticsearchに登録するIndexで使用不可文字を変更または削除する
*/
class Index final
{
  /*!
   @brief  デフォルトコンストラクタ
  */
  Index() = delete;

public:
  /*!
   @brief      コンストラクタ
   @param[in]  index confファイルに設定されたindex文字列
  */
  explicit Index(std::string index);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~Index() = default;

  /*!
   @brief      保持しているindexを返す
   @return     index
  */
  std::string get() const;

private:
  std::string index_;  //!< 文字が調整され使用可能となったIndex

  /*!
   @brief       使用禁止文字を変換する
   @note        可能な限り使用禁止文字に近い形で文字を変換する。<br>
   大文字 → 小文字、空白 → アンダースコア
  */
  void convertCharactor();
};

}  // namespace analyzer
