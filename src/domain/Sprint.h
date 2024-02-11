/*!
 @file      Sprint.h
 @brief     スプリントデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include <optional>
#include <string>
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
    Sprint( Id id, Name name, StartDate startDate, EndDate endDate );

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
    void addItem( Id itemId, std::unique_ptr<Item> item );

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

    Id id() { return id_; };
    Name name() { return name_; };

    void printChild();
    
private:
    const Id id_;                                  //!< Sprint ID
    const Name name_;                              //!< Sprint名称
    ProjectId projectId_;                          //!< 親のID
    Point totalPoint_;                             //!< プロジェクトの総見積もりポイント
    std::string status_;                           //!< スプリントのステータス（未完了open/完了closeを表す）
    StartDate startDate_;
    EndDate endDate_;
    std::map<Id, std::shared_ptr<Item>> items_;    //!< アイテムリスト
};

}
