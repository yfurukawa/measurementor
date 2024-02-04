/*!
 @file      Pts.h
 @brief     PTSとインターフェースするクラスの抽象
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <memory>
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
     @brief      全てのアクティブプロジェクトを収集する
     @param[out] アクティブプロジェクトのリスト
    */
    virtual void collectAllActiveProject( std::list<std::shared_ptr<Project>>& projectList ) = 0;

protected:
    
};

}
