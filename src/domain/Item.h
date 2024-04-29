/*!
 @file      Item.h
 @brief     プロダクトバックログデータ
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include "JsonCreator.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     Item
 @brief     プロダクトバックログデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したワークパッケージの情報の内、
            プロダクトバックログアイテムに相当するデータを保持するものである。<br>
            対応するタイプの想定は、Featureである。
*/
class Item final
{
private:
  /*!
   @brief  デフォルトコンストラクタ
  */
  Item() = delete;

public:
  /*!
   @brief  コンストラクタ
   @param[in]  itemId  このItemのID
   @param[in]  itemName  このItemの名称
   @param[in]  projectId  このItemが定義されているProjectのID
   @param[in]  sprintId   このItemが割り当てられているSprintのID<br>Sprintに未割り当ての場合の値は0
   @param[in]  storyPoint  このItemの見積もりPoint<br>見積もられていない場合の値は0
   @param[in]  status     このItemの完了状態を表すステータス
   @param[in]  statusCode このItemの完了状態を表すステータスの番号
   @param[in]  totalEstimatedTime このItemを構成するTaskの見積もり時間の合計
  */
  Item(ItemId itemId, Name itemName, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status, StatusCode statusCode,
       EstimatedTime totalEstimatedTime);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~Item() = default;

  /*!
   @brief      ストーリポイント集計のため、自身のスプリントに対してポイントを回答する
   @param[in]  sprintId  割り当てられているスプリントのID
   @return     見積もったユーザーストーリーポイント
  */
  Point reportStoryPoint(SprintId sprintId);

  /*!
   @brief      残作業時間集計のため、自身のスプリントに対した残っている作業時間（見積もり時間ベース）を回答する
   @param[in]  sprintId  割り当てられているスプリントのID
   @return     残作業時間[H]
  */
  EstimatedTime reportRemainingWorkTime(SprintId sprintId);

  /*!
   @brief      自身の情報からJsonオブジェクトを生成して返す
   @param[in]  timestamp  Jsonオブジェクトの生成日時
   @return     JSONオブジェクト（文字列）
  */
  std::string createJson(const Timestamp& timestamp);

private:
  const ItemId itemId_;               //!< Item ID
  const Name itemName_;               //!< Item名称
  ProjectId projectId_;               //!< 所属するプロジェクトのID
  Point storyPoint_;                  //!< 見積もりポイント
  Status status_;                     //!< PBLの完了状態を示す
  StatusCode statusCode_;             //!< タスクの状態を表す番号
  SprintId sprintId_;                 //!< 割り当てられたスプリントのID
  EstimatedTime totalEstimatedTime_;  //!< タスクの総見積もり時間
  JsonCreator jsonCreator_;           //!< JSON Objectを生成するクラスのインスタンス

  /*!
   @brief      自身がオープン（未完了）のタスクか回答する
   @return     true ： オープン状態
  */
  bool isOpen();
};

}  // namespace measurementor
