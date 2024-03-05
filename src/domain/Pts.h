/*!
 @file      Pts.h
 @brief     PTSとインターフェースするクラスの抽象
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
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
    virtual std::list<std::map<std::string, std::string>>  collectAllActiveProject() = 0;

    /*!
     @brief          指定されたプロジェクトに定義されているSprint情報を収集する
     @param[in]      project 収集したいプロジェクト
    */
    virtual std::list<std::map<std::string, std::string>> collectSprintInformationOf( const measurementor::ProjectId& projectId ) = 0;
    
    /*!
     @brief          指定されたプロジェクトに定義されているItemの情報を収集する
     @param[in]      project 収集したいプロジェクト
    */
    virtual std::list<std::map<std::string, std::string>> collectItemInformation( measurementor::ProjectId& projectId ) = 0;

    /*!
     @brief          指定されたプロジェクトに定義されているTaskの情報を収集する
     @param[in]      project 収集したいプロジェクト
    */
    virtual std::list<std::map<std::string, std::string>> collectTaskInformation( measurementor::ProjectId& projectId ) = 0;

protected:
    
};

}
