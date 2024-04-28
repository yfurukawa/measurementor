/*!
 @file      JsonParser.h
 @brief     Json文字列を解析して必要なデータを抽出する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "Chronos.h"
#include "DifferAbsorber.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     JsonParser
 @brief     Json文字列を解析して必要なデータを抽出する
 @note      本クラスは、OpenProjectから受信したJson文字列から必要な情報を抽出し、それを返すものである。
*/
class JsonParser
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  JsonParser();

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~JsonParser() = default;

  /*!
   @brief        Json文字列からProjectの情報を抽出する
   @param[in]    入力となるJson文字列
   @return       抽出情報（Projectの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectProjectData(const std::string& jsonString);

  /*!
   @brief        Json文字列からSprintの情報を抽出する
   @param[in]    入力となるJson文字列
   @return       抽出情報（Sprintの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectSprintData(const std::string& jsonString);

  /*!
   @brief        Json文字列からPBIの情報を抽出する
   @param[in]    入力となるJson文字列
   @return       抽出情報（PBIの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectItemData(const std::string& jsonString);

  /*!
   @brief        Json文字列からTaskの情報を抽出する
   @param[in]    入力となるJson文字列
   @return       抽出情報（タスクの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> collectTaskData(const std::string& jsonString);

protected:
  std::unique_ptr<Chronos> timeConverter_;           //!< OpenProjectから取得したデータ内に含まれるローカルタイムをGMTに変換するクラス
  std::unique_ptr<DifferAbsorber> differAbsober_;    //!< カスタマイズしたステータスを持つOpenProjectのステータスをデフォルト設定に変換するクラス

  /*!
   @brief        Json文字列のparent::hrefからidを抽出する
   @param[in]    入力となるJson文字列
   @return       抽出したidの文字列
  */
  std::string pickupId(std::string href);

  /*!
   @brief        Json文字列のremainingTimeの設定値（PTxH）から数値を抽出する
   @param[in]    remainingTimeの設定値
   @return       時間を表す数値（文字列）
  */
  std::string pickupHour(std::string remainingTimeValue);
};

}  // namespace pts
