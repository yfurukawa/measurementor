/*!
 @file      Item.h
 @brief     プロダクトバックログデータ
*/
#pragma once

// ---------------< include >----------------------------
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
     @param[in]  id  このItemのID
     @param[in]  name  このItemの名称
     @param[in]  projectId  このItemが定義されているProjectのID
     @param[in]  sprintId   このItemが割り当てられているSprintのID<br>Sprintに未割り当ての場合の値は0
     @param[in]  storyPoint  このItemの見積もりPoint<br>見積もられていない場合の値は0
     @param[in]  status     このItemの完了状態を表すステータス
    */
    Item( Id id, Name name, ProjectId projectId, SprintId sprintId, Point storyPoint, Status status );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Item() = default;

    /*!
     @brief      ItemをSprintに割り当てる
     @param[in]  id SprintのID
    */
    void assignSprint( SprintId sprintId );

    /*!
     @brief      Itemにタスクを追加する
     @param[in]  task 追加するタスク
    */
    void addTask( std::shared_ptr<Task> task );

    /*!
     @brief      親となるバージョンのIDを返す
     @return     バージョンのID
    */
    std::optional<SprintId> sprintId() const;

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

    /*!
     @brief      残っている作業時間（見積もり時間ベース）を報告する
    */
    EstimatedTime reportRemainingWorkTime();

    /*!
     @brief      ストーリポイント集計のため、ポイントを回答する
     @return     ポイント
    */
    Point point()
    {
        return storyPoint_;
    }

    /*!
     @brief      自身の情報からJSONオブジェクトを生成して返す
     @return     JSONオブジェクト（文字列）
    */
    std::string createJson();

    Id id() { return id_; };
    Name name() { return name_; };

    void printChild();
    
private:
    const Id id_;                                  //!< Item ID
    const Name name_;                              //!< Item名称
    ProjectId projectId_;                          //!< 所属するプロジェクトのID
    Point storyPoint_;                             //!< 見積もりポイント
    Status status_;                                //!< PBLの完了状態を示す
    SprintId sprintId_;                            //!< 割り当てられたスプリントのID
    EstimatedTime totalEstimatedTime_;             //!< タスクの総見積もり時間
    std::map<Id, std::shared_ptr<Task>> tasks_;    //!< タスクリスト
    JsonCreator jsonCreator_;                      //!< JSON Objectを生成するクラスのインスタンス
};

}
