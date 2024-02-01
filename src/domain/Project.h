/*!
 @file      Project.h
 @brief     プロジェクトデータ
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     Pts
 @brief     プロジェクトデータ
 @note      本クラスは、Project Tracking System (PTS) から取得したプロジェクトの情報の内、メトリックスの算出に必要となるデータを保持するものである。<br>
 又、PTS内ではプロジェクトが子プロジェクトを持つことが想定されるため、その状況にも対応可能にしておく。
*/
class Project
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Project() : point_(0)
    {
        childProjects_.clear();
    };

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Project() = default;

private:
    PointRaw<uint8_t> point_;               //!< プロジェクトの総見積もりポイント
    std::list<Project> childProjects_;    //!< 子プロジェクトのリスト
};

}
