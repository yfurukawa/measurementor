/*!
 @file      JsonParser.h
 @brief     Json文字列を解析して必要なデータを抽出する
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "../../domain/Project.h"
#include "nlohmann/json.hpp"
#include "../../../lib/libclock/Chronos.h"

// ---------< forward declaration (Global) >-------------
namespace measurementor
{
    class Project;
    class Item;
    class Task;
}

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     JsonParser
 @brief     Json文字列を解析して必要なデータを抽出する
 @note      本クラスは、OpenProjectから受信したJson文字列から必要な情報を抽出し、それを返すものである。
*/
class JsonParser final
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    JsonParser() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~JsonParser() = default;

    /*!
     @brief        Json文字列からプロジェクトオブジェクトリストを作成する
     @param[in]    入力となるJson文字列
     @param[out]   作成したオブジェクトリスト
    */
    void collectProjectData( const std::string& jsonString, std::map<unsigned int, std::shared_ptr<measurementor::Project>>& projectList );

    /*!
     @brief        Json文字列からSprint情報を抽出し、プロジェクトに紐付ける
     @param[in]    入力となるJson文字列
     @param[out]   紐付けの対象であるプロジェクト
    */
    void collectSprintData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project );

    /*!
     @brief        Json文字列からPBLとTaskの情報を抽出し、紐付ける
     @param[in]    入力となるJson文字列
     @param[out]   対象プロジェクト
     @attention    TODO delete
    */
    void collectPBLandTaskData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project );

    /*!
     @brief        Json文字列からSprintの情報を抽出する
     @param[in]    入力となるJson文字列
     @return       抽出情報（Sprintの情報マップをリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectSprintData( const std::string& jsonString );

    /*!
     @brief        Json文字列からPBIの情報を抽出する
     @param[in]    入力となるJson文字列
     @return       抽出情報（PBIの情報マップをリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectItemData( const std::string& jsonString );

    /*!
     @brief        Json文字列からTaskの情報を抽出する
     @param[in]    入力となるJson文字列
     @return       抽出情報（タスクの情報マップをリスト化したもの）
    */
    std::list<std::map<std::string, std::string>> collectTaskData( const std::string& jsonString );

private:
    std::shared_ptr<measurementor::Item> extractPBLData( nlohmann::json jsonString, int count );
    std::shared_ptr<measurementor::Task> extractTaskData( nlohmann::json jsonString, int count );
    ::Chronos chronos_;

    /*!
     @brief        Json文字列のparent::hrefから親プロジェクトのidを抽出する
     @param[in]    入力となるJson文字列
     @param[out]   作成したオブジェクトリスト
    */
    unsigned int pickupId( std::string href );

    /*!
     @brief        Json文字列のremainingTimeの設定値（PTxH）から数値を抽出する
     @param[in]    remainingTimeの設定値
     @return       時間を表す数値（文字列）
    */
    std::string pickupHour( std::string remainingTimeValue );



};

}
