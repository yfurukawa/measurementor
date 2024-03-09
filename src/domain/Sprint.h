/*!
 @file      Sprint.h
 @brief     スプリントデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include <string>
#include "JsonCreator.h"
#include "domainPrimitives/MeasurementPrimitives.h"


// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Item;

/*!
 @class     Sprint
 @brief     スプリントデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したバージョンの情報の内、スプリントに相当するデータを保持するものである。<br>
 OpenProjectでは、ある期間を表すのにVersionを用いるが直感的ではないので、SCRUMの用語であるSprintを用いることとする。
*/
class Sprint final
{
private:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Sprint() = delete;

public:
    /*!
     @brief  コンストラクタ
    */
    Sprint( ProjectId projectId, SprintId sprintId, Name sprintName, Status status, StartDate startDate, EndDate endDate );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Sprint() = default;

    /*!
     @brief      残りの作業時間（見積もりベース）を集計する
     @note       残りの作業時間を集計することでスプリントバーンダウンチャートを作成する
    */
    void aggrigateRemainingWorkTime( std::map<ItemId, std::shared_ptr<Item>> itemList );

    /*!
     @brief      ストーリポイント集計のため、自身のプロジェクトに対してポイントを回答する
     @return     ポイント
    */
    Point reportStoryPoint( ProjectId blongingProject );

    /*!
     @brief      残りのユーザーストーリーポイントを登録する
     @param[in]  remainingStoryPint  プロジェクト毎に集計した残ユーザーストーリーポイント
    */
    void registerStoryPoint( Point remainingStoryPint );

    /*!
     @brief      自身の情報からJSONオブジェクトを生成して返す
     @param[in]  timestamp elasticserchに登録する際に使用する日時（ISO8601の拡張型GMT形式）
     @return     JSONオブジェクト（文字列）
    */
    std::string createJson( const Timestamp& timestamp );

private:
    const SprintId sprintId_;                      //!< Sprint ID
    const Name sprintName_;                        //!< Sprint名称
    ProjectId projectId_;                          //!< 親のID
    Point totalPoint_;                             //!< スプリントに割り当てられたアイテムの総見積もりポイント
    Status status_;                                //!< スプリントのステータス（未完了open/完了closeを表す）
    StartDate startDate_;                          //!< スプリント開始日
    EndDate endDate_;                              //!< スプリント終了日
    EstimatedTime remainingEstimatedTime_;         //!< タスクの残見積もり時間（スプリントバーンダウンチャート用）
    JsonCreator jsonCreator_;                      //!< JSON Objectを生成するクラスのインスタンス
};

}
