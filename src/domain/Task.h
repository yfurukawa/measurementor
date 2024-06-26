/*!
 @file      Task.h
 @brief     タスクデータ
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "JsonCreator.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class MetricCalculator;   //!< 

/*!
 @class     Task
 @brief     タスクデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したワークパッケージの情報の内、
            タスクに相当するデータを保持するものである。
*/
class Task final
{
private:
   //! タスクのメトリックスを測定するクラス。以下の理由によりフレンドクラスとしている。<br>
   //! ・新旧２つのタスククラスの属性を使用してメトリックスを計算する<br>
   //! ・Taskのメトリックスの計算をするクラスであり、Taskのメンバ関数と同等の位置づけである<br>
   //! ・Taskにgetterを実装するよりTaskのカプセル化を維持できる

  friend MetricCalculator;

  /*!
   @brief  デフォルトコンストラクタ
  */
  Task() = delete;

public:
  /*!
   @brief  コンストラクタ
   @param[in]  projectId       このTaskが定義されているProjectのID
   @param[in]  projectName     このTaskが定義されているProjectの名称
   @param[in]  sprintId        このTaskが割り当てられているSprintのID<br>Sprintに未割り当ての場合の値は0
   @param[in]  sprintName      このTaskが割り当てられているSprintの名称
   @param[in]  taskId          このTaskのID
   @param[in]  taskName        このTaskの名称
   @param[in]  author          このタスクの作成者
   @param[in]  itemId          このTaskが割り当てられているItemのID<br>Itemに未割り当ての場合の値は0
   @param[in]  estimatedTime   このTaskの見積もり作業時間[H]
   @param[in]  assignee        このタスクの担当者
   @param[in]  status          このタスクの状態
   @param[in]  statusCode      このタスクの状態を表すコード
   @param[in]  updatedAt       このTaskを更新した日時（ISO8601形式）
  */
  Task(ProjectId projectId, Name projectName, SprintId sprintId, Name sprintName, ItemId itemId, TaskId taskId, Name taskName, Author author, EstimatedTime estimatedTime,
       Assignee assignee, Status status, StatusCode statusCode, UpdatedAt updatedAt);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~Task() = default;

  /*!
   @brief      自身の情報からJSONオブジェクトを生成して返す
   @return     JSONオブジェクト（文字列）
  */
  std::string createJson(Timestamp timestamp);

private:
  const ProjectId projectId_;    //!< 所属するプロジェクトのID
  const Name projectName_;       //!< 所属するプロジェクトの名称
  const SprintId sprintId_;      //!< 割り当てられたスプリントのID
  const Name sprintName_;        //!< 割り当てられたスプリントの名称
  const ItemId itemId_;          //!< Taskを持つItemのID
  const TaskId taskId_;          //!< Task ID
  const Name taskName_;          //!< Task名称
  const Author author_;          //!< タスクの作成者
  EstimatedTime estimatedTime_;  //!< 見積もり時間[H]
  Assignee assignee_;            //!< タスクの担当者
  Status status_;                //!< タスクの状態
  StatusCode statusCode_;        //!< タスクの状態を表す番号
  UpdatedAt updatedAt_;          //!< タスク内容の更新日時（ISO8601形式）
  JsonCreator jsonCreator_;      //!< JSON Objectを生成するクラスのインスタンス

  /*!
   @brief      自身がオープン（未完了）のタスクか回答する
   @return     true ： オープン状態
  */
  bool isOpen();
};

}  // namespace measurementor
