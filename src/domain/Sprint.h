/*!
 @file      Sprint.h
 @brief     スプリントデータ
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
    Sprint( Id id, Name name, Status status, StartDate startDate, EndDate endDate );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Sprint() = default;

    /*!
     @brief      SprintをProjectに割り当てる
     @param[in]  id 割当先ProjectのID
    */
    void assignProject( ProjectId projectId );

    /*!
     @brief      Sprintにアイテムを追加する
     @param[in]  id アイテムのID
    */
    void addItem( std::shared_ptr<Item> item );

    /*!
     @brief      親となるプロジェクトのIDを返す
     @return     プロジェクトのID
    */
    std::optional<ProjectId> projectId() const;

    /*!
     @brief      割り当てられたアイテムの有無を返す
     @return     true : アイテムあり
    */
    bool hasChild() const
    {
        return !items_.empty();
    }

    /*!
     @brief      アイテムのストーリーポイントを集計する
    */
    void aggrigateStoryPoint();

    /*!
     @brief      残りの作業時間（見積もりベース）を集計する
     @note       残りの作業時間を集計することでスプリントバーンダウンチャートを作成する
    */
    void aggrigateRemainingWorkTime();

    /*!
     @brief      ストーリポイント集計のため、ポイントを回答する
     @return     ポイント
    */
    Point reportStoryPoint();

    /*!
     @brief      自身の情報からJSONオブジェクトを生成して返す
     @return     JSONオブジェクト（文字列）
    */
    std::string createJson();

    /*!
     @brief      割り当てられたProduct Backlog ItemにJSONオブジェクト生成を指示する
     @return     JSONオブジェクト（文字列）
    */
    std::optional<std::list<std::string>> createJsonOfItem();

    Id id() { return id_; };
    Name name() { return name_; };

    void printChild();
    
private:
    const Id id_;                                  //!< Sprint ID
    const Name name_;                              //!< Sprint名称
    ProjectId projectId_;                          //!< 親のID
    Point totalPoint_;                             //!< スプリントに割り当てられたアイテムの総見積もりポイント
    Status status_;                           //!< スプリントのステータス（未完了open/完了closeを表す）
    StartDate startDate_;                          //!< スプリント開始日
    EndDate endDate_;                              //!< スプリント終了日
    EstimatedTime remainingEstimatedTime_;         //!< タスクの残見積もり時間（スプリントバーンダウンチャート用）
    std::map<Id, std::shared_ptr<Item>> items_;    //!< アイテムリスト
    JsonCreator jsonCreator_;                      //!< JSON Objectを生成するクラスのインスタンス
};

}
