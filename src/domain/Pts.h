/*!
 @file      Pts.h
 @brief     PTSとインターフェースするクラスの抽象
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include "Project.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     Pts
 @brief     PTSとインターフェースするクラスの抽象
 @note      本クラスは、Project Tracking System (PTS) からプロジェクトの情報を取得し、メトリックスの算出ができるように
 加工するクラスのための抽象クラスである。
*/
class Pts
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Pts() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~Pts() = default;

    /*!
     @brief  全てのアクティブプロジェクトを収集する
     @return アクティブプロジェクトのリスト
    */
    virtual std::list<Project> collectAllActiveProject() = 0;

protected:
    std::list<Project> projectList_;          //!< OpenProject内で管理されているアクティブなプロジェクト一覧
};

}
