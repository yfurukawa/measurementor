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
     @param[in]  id Task ID
     @param[in]  name Task名称
     @param[in]  author タスクの作成者
     @param[in]  itemId Taskを持つItemのID
     @param[in]  estimateTime 見積もりポイント
     @param[in]  assignee タスクの担当者
     @param[in]  status タスクの状態
     @param[in]  updatedAt 更新日時（ISO8601形式）
    */
    Task( Id id, Name name, Author author, ItemId itemId, EstimateTime estimateTime, Assignee assignee, Status status, StatusCode statusCode, UpdatedAt updatedAt );

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
     @param[in]  time 見積もり時間
    */
    void estimateWorkTime( EstimateTime time )
    {
        swap( estimateTime_, time );
    }

    /*!
     @brief      担当者を割り当てる
     @param[in]  assignee  担当者名
    */
    void assignAsignee( Assignee assignee )
    {
        swap( assignee_, assignee );
    }

    /*!
     @brief      ステータスを更新する
     @param[in]  newStatus  新しい状態
    */
    void updateStatus( unsigned int newStatus );

    /*!
     @brief      見積もり時間を回答する
     @return     見積もり時間
    */
    EstimateTime estimateTime() const
    {
        return estimateTime_;
    };

    Id id() { return id_; };
    Name name() { return name_; };
    
private:
    const Id id_;                 //!< Task ID
    const Name name_;             //!< Task名称
    const Author author_;         //!< タスクの作成者
    const ItemId itemId_;         //!< Taskを持つItemのID
    EstimateTime estimateTime_;   //!< 見積もりポイント
    Assignee assignee_;           //!< タスクの担当者
    Status status_;               //!< タスクの状態
    StatusCode statusCode_;       //!< タスクの状態を表す番号
    UpdatedAt updatedAt_;         //!< タスク内容の更新日時（ISO8601形式）
};

}
