/*!
 @file      DifferAbsorber.h
 @brief     Json文字列を解析して必要なデータを抽出する際にデフォルト設定のOpenProjectとカスタマイズした設定の
 違いを吸収し、オリジナル設定に寄せる
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "Chronos.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     JsonParser
 @brief     Json文字列を解析して必要なデータを抽出する
 @note      本クラスは、OpenProjectから受信したJson文字列から必要な情報を抽出し、それを返すものである。
*/
class DifferAbsorber final
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  DifferAbsorber() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  ~DifferAbsorber() = default;

  /*!
   @brief        ステータスコードを元にタスクのステータス名称をデフォルトの名称に変更する
   @param[in]    customizedStatusCode  カスタマイズされたステータスコード
   @return       対応するデフォルトのステータス名称
  */
  std::string convertStatusName(std::string customizedStatusCode, std::string customizedStatusName);

  /*!
   @brief        タスクのステータスコードをデフォルトのコードに変更する
   @param[in]    customizedStatusCode  カスタマイズされたステータスコード
   @return       対応するデフォルトのステータスコード
  */
  std::string convertStatusCode(std::string customizedStatusCode);

  /*!
   @brief        タイプコードを元にデフォルトのタイプ名称に変更する
   @param[in]    customizedTypeCode  カスタマイズされたタイプコード
   @return       対応するデフォルトのタイプ名称
  */
  std::string convertTypeName(std::string customizedTypeCode, std::string customizedTypeName);

  /*!
   @brief        タイプのコードをデフォルトのタイプコードに変更する
   @param[in]    customizedTypeCode  カスタマイズされたタイプコード
   @return       対応するデフォルトのタイプコード
  */
  std::string convertTypeCode(std::string customizedTypeCode);  

};

} // namespace pts
