/*!
 @file      Project.h
 @brief     プロジェクトデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
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
    Project( Id id, Name name );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Project() = default;

    /*!
     @brief      子プロジェクトを追加する
     @param[in]  id 子プロジェクトのプロジェクトID
     @param[in]  childProject 子プロジェクト
    */
    void addChildProject( Id childProjectId, std::shared_ptr<Project> childProject );

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
            std::cout << "   " << p->first << " : " << p->second->name() << std::endl;
        }
    }
    
private:
    const Id id_;               //!< Project ID
    const Name name_;           //!< Project名称
    Point point_;         //!< プロジェクトの総見積もりポイント
    std::map<unsigned int, std::shared_ptr<Project>> childProjects_;   //!< 子プロジェクトのリスト
};

}
