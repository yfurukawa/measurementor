/*!
 @file      Item.h
 @brief     プロダクトバックログデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include <optional>
#include "domainPrimitives/MeasurementPrimitives.h"

#include <string>
#include <iostream>
// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Task;

/*!
 @class     Item
 @brief     プロダクトバックログデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したワークパッケージの情報の内、プロダクトバックログアイテムに相当するデータを保持するものである。<br>
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
    */
    Item( Id id, Name name );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Item() = default;

    /*!
     @brief      ItemをVersionに割り当てる
     @param[in]  id VersionのID
    */
    void assignVersion( VersionId versionId );

    /*!
     @brief      Itemにタスクを追加する
     @param[in]  id タスクのID
    */
    void addTask( Id taskId, std::shared_ptr<Task> task );

    /*!
     @brief      親となるバージョンのIDを返す
     @return     バージョンのID
    */
    std::optional<VersionId> versionId() const;

    /*!
     @brief      子プロジェクトの有無を返す
     @return     true : 子プロジェクトあり
    */
    bool hasChild() const
    {
        return !tasks_.empty();
    }

    /*!
     @brief      タスクの見積もり時間を集計する
    */
    void aggrigateEstimatedTime();

    Id id() { return id_; };
    Name name() { return name_; };

    void printChild();
    
private:
    const Id id_;                                  //!< Item ID
    const Name name_;                              //!< Item名称
    VersionId versionId_;                          //!< 親のID
    Point point_;                                  //!< プロジェクトの総見積もりポイント
    EstimateTime totalEstimateTime_;               //!< タスクの総見積もり時間
    std::map<Id, std::shared_ptr<Task>> tasks_;    //!< タスクリスト

};

}
