/*!
 @file      Project.h
 @brief     プロジェクトデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"

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

private:
    Id id_;               //!< Project ID
    Name name_;           //!< Project名称
    Point point_;         //!< プロジェクトの総見積もりポイント
    std::list<Project> childProjects_;   //!< 子プロジェクトのリスト
};

}
