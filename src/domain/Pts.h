/*!
 @file      Pts.h
 @brief     PTSとインターフェースするクラスの抽象
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"

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
     @brief   全てのアクティブプロジェクトを収集する
     @return  アクティブプロジェクトのリスト（Projectの情報マップ（情報名、値）をリスト化したもの）
    */
    virtual std::list<std::map<std::string, std::string>>  collectAllActiveProject() = 0;

    /*!
     @brief          指定されたプロジェクトに定義されているSprint情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）
    */
    virtual std::list<std::map<std::string, std::string>> collectSprintInformation( const measurementor::ProjectId& projectId ) = 0;
    
    /*!
     @brief          指定されたプロジェクトに定義されているItemの情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         プロダクトバックログアイテムのリスト（PBIの情報マップ（情報名、値）をリスト化したもの）
    */
    virtual std::list<std::map<std::string, std::string>> collectItemInformation( const measurementor::ProjectId& projectId ) = 0;

    /*!
     @brief          指定されたプロジェクトに定義されているTaskの情報を収集する
     @param[in]      project 収集したいプロジェクト
     @return         タスクのリスト（タスクの情報マップ（情報名、値）をリスト化したもの）
    */
    virtual std::list<std::map<std::string, std::string>> collectTaskInformation( const measurementor::ProjectId& projectId ) = 0;

protected:
    
};

}
