/*!
 @file      Task.h
 @brief     タスクデータ
*/
#pragma once

// ---------------< include >----------------------------
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     Task
 @brief     タスクデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したワークパッケージの情報の内、タスクに相当するデータを保持するものである。
*/
class Task final
{
private:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Task() = delete;

public:
    /*!
     @brief  コンストラクタ
    */
    Task( Id id, Name name, Author author, ItemId itemId );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Task() = default;

    /*!
     @brief      親となるバージョンのIDを返す
     @return     バージョンのID
    */
    ItemId itemId() const
    {
        return itemId_;
    }

    /*!
     @brief      作業時間を見積もる
     @return     見積もり時間
    */
    void estimateWorkTime( EstimateTime time )
    {
        swap( estimateTime_, time );
    }

    /*!
     @brief      担当者を割り当てる
     @return     担当者名
    */
    void assignAsignee( Assignee assignee )
    {
        swap( assignee_, assignee );
    }

    /*!
     @brief      ステータスを更新する
     @return     バージョンのID
    */
    void updateStatus( unsigned int newStatus );

    Id id() { return id_; };
    Name name() { return name_; };
    
private:
    const Id id_;                 //!< Project ID
    const Name name_;             //!< Project名称
    const Author author_;         //!< タスクの作成者
    const ItemId itemId_;         //!< 親のID
    EstimateTime estimateTime_;   //!< プロジェクトの総見積もりポイント
    Assignee assignee_;            //!< タスクの担当者
    unsigned int status_;         //!< タスクの状態
};

}
