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
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Project() : id_(0), name_(""), point_(0)
    {
        childProjects_.clear();
    };

    /*!
     @brief  コンストラクタ
    */
    Project( Id<unsigned int> id, Name<std::string> name ) : id_(id), name_(std::move(name)), point_(0){};

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Project() = default;

private:
    Id<unsigned int> id_;                //!< Project ID
    Name<std::string> name_;             //!< Project名称
    Point<uint8_t> point_;               //!< プロジェクトの総見積もりポイント
    std::list<Project> childProjects_;   //!< 子プロジェクトのリスト
};

}
