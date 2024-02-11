/*!
 @file      Pts.h
 @brief     PTSとインターフェースするクラスの抽象
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
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
    virtual void collectAllActiveProject( std::map<unsigned int, std::shared_ptr<Project>>& projectList ) = 0;

    /*!
     @brief          指定されたプロジェクトに定義されているSprint情報を収集する
     @param[in,out]  project 収集したいプロジェクト
    */
    virtual void collectSprintInformationOf( std::shared_ptr<Project>& project ) = 0;
    
    /*!
     @brief          指定されたプロジェクトに定義されているPBLとTaskの情報を収集する
     @param[in,out]  project 収集したいプロジェクト
    */
    virtual void collectPBLandTaskInformation( std::shared_ptr<Project>& project ) = 0;
    
protected:
    
};

}
