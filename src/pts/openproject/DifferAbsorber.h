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
   @details      ステータスコードに対するステータを名称を以下のとおりに統一する<br>
   ステータスコード　ステータス名称<br>
   1 New<br>
   7 In Progress<br>
   15 Review<br>
   12 Closed
   @param[in]    customizedStatusCode  カスタマイズされたステータスコード
   @return       対応するデフォルトのステータス名称
  */
  std::string convertStatusName(std::string customizedStatusCode, std::string customizedStatusName);

  /*!
   @brief        タスクのステータスコードをデフォルトのコードに変更する
   @details      ステータスコードを以下のとおりに統一する<br>
   状態 ステータスコード<br>
   新規（New） 1<br>
   処理中（In Progress） 7<br>
   レビュー中（Review） 15<br>
   完了（Closed） 12
   @param[in]    customizedStatusCode  カスタマイズされたステータスコード
   @return       対応するデフォルトのステータスコード
  */
  std::string convertStatusCode(std::string customizedStatusCode);

  /*!
   @brief        タイプコードを元にデフォルトのタイプ名称に変更する
   @details      タイプコードに対するタイプを名称を以下のとおりに統一する<br>
   タイプコード　タイプ名称<br>
   1 Task<br>
   4 Feature
   @param[in]    customizedTypeCode  カスタマイズされたタイプコード
   @return       対応するデフォルトのタイプ名称
  */
  std::string convertTypeName(std::string customizedTypeCode, std::string customizedTypeName);

  /*!
   @brief        タイプのコードをデフォルトのタイプコードに変更する
   @details      タイプコードを以下のとおりに統一する<br>
   タイプ 説明 タイプコード<br>
   Task タスク 1<br>
   Feature　プロダクトバックログアイテム 4
   @param[in]    customizedTypeCode  カスタマイズされたタイプコード
   @return       対応するデフォルトのタイプコード
  */
  std::string convertTypeCode(std::string customizedTypeCode);  

  /*!
   @brief        パース対象JsonがItemのものか判断する
   @param[in]    type  データの種類を表すID
   @return       Itemである場合、trueを返す
  */
  bool isItemData(std::string type);

  /*!
   @brief        パース対象JsonがTaskのものか判断する
   @param[in]    type  データの種類を表すID
   @return       Taskである場合、trueを返す
  */
  bool isTaskData(std::string type);
};

} // namespace pts
