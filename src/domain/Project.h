/*!
 @file      Project.h
 @brief     プロジェクトデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"
#include "JsonCreator.h"

#include <iostream>
// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Sprint;
class Item;

/*!
 @class     Project
 @brief     プロジェクトデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したプロジェクトの情報の内、メトリックスの算出に必要となるデータを保持するものである。<br>
 又、PTS内ではプロジェクトが子プロジェクトを持つことが想定されるため、その状況にも対応可能にしておく。
*/
class Project final
{
private:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Project() = delete;

public:
    /*!
     @brief  コンストラクタ
    */
    Project( Id id, Name name, ParentId parentId );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Project() = default;

    /*!
     @brief      子プロジェクトと関連付ける
     @param[in]  id 子プロジェクトのプロジェクトID
    */
    void relateChildProject( Id childProjectId );

    /*!
     @brief      親プロジェクトのIDを返す
     @return     親プロジェクトのID
    */
    ParentId parentId() const
    {
        return parentId_;
    }

    /*!
     @brief      子プロジェクトの有無を返す
     @return     true : 子プロジェクトあり
    */
    bool hasChild() const
    {
        return !(childProjects_.empty()) || !(sprints_.empty()) || !(productBackLog_.empty()) ;
    }

    /*!
     @brief      Sprintを追加する
     @param[in]  sprint 追加するスプリント
    */
    void addSprint( std::shared_ptr<Sprint> sprint );

    /*!
     @brief      Product Back LogにProduct Backlog Itemを追加する
     @param[in]  pbi  Product Back Logに追加するProduct Backlog Item
    */
    void addPBL( std::shared_ptr<Item> pbi );

    /*!
     @brief      自身の情報からJSONオブジェクトを生成して返す
     @return     JSONオブジェクト（文字列）
    */
    std::string createJson();


    Id id() { return id_; };
    Name name() { return name_; };

    std::shared_ptr<Sprint> getSprint( measurementor::SprintId sprintId );

    void printChild();
    
private:
    const Id id_;                                             //!< Project ID
    const Name name_;                                         //!< Project名称
    const ParentId parentId_;                                 //!< 親のID
    Point storyPointInprogress_;                              //!< 現在進行中のSprintのユーザーストーリポイント数
    Point remaingStoryPoints_;                                //!< Product Back Logに残っているユーザストーリーの総ポイント数
    std::list<Id> childProjects_;                             //!< 子プロジェクトのIDリスト
    std::map<Id, std::shared_ptr<Sprint>> sprints_;           //!< Project内に定義されたSprint
    std::map<Id, std::shared_ptr<Item>> productBackLog_;      //!< ProjectのProduct Backlog Item
    JsonCreator jsonCreator_;                                 //!< JSON Objectを生成するクラスのインスタンス
};

}
