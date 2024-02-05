/*!
 @file      Project.h
 @brief     プロジェクトデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <memory>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"

#include <iostream>
// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     Project
 @brief     プロジェクトデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したプロジェクトの情報の内、メトリックスの算出に必要となるデータを保持するものである。<br>
 又、PTS内ではプロジェクトが子プロジェクトを持つことが想定されるため、その状況にも対応可能にしておく。
*/
class Project
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
     @brief      子プロジェクトの有無を返す
     @return     true : 子プロジェクトあり
    */
    bool hasChild() const
    {
        return !childProjects_.empty();
    }

    Id id() { return id_; };
    Name name() { return name_; };

    void printChild()
    {
        for( auto p = childProjects_.begin(); p != childProjects_.end(); ++p )
        {
            std::cout << "   " << *p << std::endl;
        }
    }
    
private:
    const Id id_;                   //!< Project ID
    const Name name_;               //!< Project名称
    const ParentId parentId_;       //!< 親のID
    Point point_;                   //!< プロジェクトの総見積もりポイント
    std::list<Id> childProjects_;   //!< 子プロジェクトのIDリスト
};

}
