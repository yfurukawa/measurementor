/*!
 @file      Item.h
 @brief     プロダクトバックログデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"
#include "JsonCreator.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Task;

/*!
 @class     Item
 @brief     プロダクトバックログデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したワークパッケージの情報の内、
            プロダクトバックログアイテムに相当するデータを保持するものである。<br>
            対応するタイプの想定は、Feature及びUser Storyである。
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
    */
    Item( ItemId itemId, Name itemName, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status, StatusCode statusCode, EstimatedTime totalEstimatedTime );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Item() = default;

    /*!
     @brief      残っている作業時間（見積もり時間ベース）を報告する
    */
    EstimatedTime reportRemainingWorkTime( SprintId sprintId );

    /*!
     @brief      自身の情報からJSONオブジェクトを生成して返す
     @return     JSONオブジェクト（文字列）
    */
    std::string createJson( const Timestamp& timestamp );
    
private:
    const ItemId itemId_;                          //!< Item ID
    const Name itemName_;                          //!< Item名称
    ProjectId projectId_;                          //!< 所属するプロジェクトのID
    Point storyPoint_;                             //!< 見積もりポイント
    Status status_;                                //!< PBLの完了状態を示す
    StatusCode statusCode_;                        //!< タスクの状態を表す番号
    SprintId sprintId_;                            //!< 割り当てられたスプリントのID
    EstimatedTime totalEstimatedTime_;             //!< タスクの総見積もり時間
    JsonCreator jsonCreator_;                      //!< JSON Objectを生成するクラスのインスタンス

    /*!
     @brief      自身がオープン（未完了）のタスクか回答する
     @return     true ： オープン状態
    */
    bool isOpen();

    /*!
     @brief      自身がオープンの場合に、ストーリポイント集計のため、ポイントを回答する
     @return     ポイント
    */
    Point reportStoryPoint();
};

}
