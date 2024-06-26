/*!
 @file      JsonCreator.h
 @brief     与えられた値のペアを保持し、それらからJSON文字列を作成する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <cstdint>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"
#include "nlohmann/json.hpp"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class      JsonCreator
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
  void holdData(JsonKey key, std::string stringValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  intValue 値
  */
  void holdData(JsonKey key, int intValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  intValue 値
  */
  void holdData(JsonKey key, std::uint_fast16_t intValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  longValue 値
  */
  void holdData(JsonKey key, long longValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  doubleValue 値
   @note       floatは実数の精度が悪いので使用しないほうが良い
  */
  void holdData(JsonKey key, double doubleValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  boolValue 値
  */
  void holdData(JsonKey key, bool boolValue);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  jsonObject 値（文字列）
  */
  void holdData(JsonKey key, JsonObject jsonObject);

  /*!
   @brief      キーと値（文字列）を受け取る
   @param[in]  key キー
   @param[in]  jsonObject 値（文字列）
  */
  void holdDataAsArray(JsonKey key, JsonObject jsonObject);

  /*!
   @brief      保持しているデータからJson文字列を生成する
   @return     生成されたJson文字列
  */
  std::string createJson();

private:
  nlohmann::json jsonRaw_;  //!< Jsonの元データ
};

}  // namespace measurementor
