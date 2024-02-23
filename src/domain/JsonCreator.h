/*!
 @file      JsonCreator.h
 @brief     与えられた値のペアを保持し、それらからJSON文字列を作成する
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "nlohmann/json.hpp"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @file      JsonCreator.h
 @brief     与えられた値のペアを保持し、それらからJSON文字列を作成する
 @note      本クラスは、キーと値のペアを複数受取り、それらからJSON文字列を生成するものである。
*/
class JsonCreator
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    JsonCreator();

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~JsonCreator() = default;

    /*!
     @brief      キーと値（文字列）を受け取る
     @param[in]  key キー
     @param[in]  stringValue 値（文字列）
    */
    void holdData( std::string key, std::string stringValue );

    /*!
     @brief      キーと値（文字列）を受け取る
     @param[in]  key キー
     @param[in]  intValue 値（文字列）
    */
    void holdData( std::string key, int intValue );

    /*!
     @brief      キーと値（文字列）を受け取る
     @param[in]  key キー
     @param[in]  longValue 値（文字列）
    */
    void holdData( std::string key, long longValue );

    /*!
     @brief      キーと値（文字列）を受け取る
     @param[in]  key キー
     @param[in]  doubleValue 値（文字列）
    */
    void holdData( std::string key, double doubleValue );

    /*!
     @brief      キーと値（文字列）を受け取る
     @param[in]  key キー
     @param[in]  boolValue 値（文字列）
    */
    void holdData( std::string key, bool boolValue );

    /*!
     @brief          保持しているデータからJson文字列を生成する
     @param[in,out]  生成されたJson文字列
    */
    std::string createJson();
    
private:
    nlohmann::json jsonRaw_;    //!< Jsonの元データ
    
};

}
