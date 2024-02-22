/*!
 @file      JsonParser.h
 @brief     Json文字列を解析して必要なデータを抽出する
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include <string>
#include "../../domain/Project.h"
#include "nlohmann/json.hpp"

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
 @note      本クラスは、OpenProjectから受信したJson文字列から必要な情報を抽出し、オブジェクトリストを返すものである。
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
    */
    void collectPBLandTaskData( const std::string& jsonString, std::shared_ptr<measurementor::Project>& project );

private:
    /*!
     @brief        Json文字列のparent::hrefから親プロジェクトのidを抽出する
     @param[in]    入力となるJson文字列
     @param[out]   作成したオブジェクトリスト
    */
    unsigned int pickupId( std::string href );

    std::shared_ptr<measurementor::Item> extractPBLData( nlohmann::json jsonString, int count );
    std::shared_ptr<measurementor::Task> extractTaskData( nlohmann::json jsonString, int count );
};

}
