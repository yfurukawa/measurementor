/*!
 @file      IPreviousDataReader.h
 @brief
 ptsとインターフェースクラスが生成したPreviousTask_x.jsonファイルを読み込み、メトリックス取得に必要なデータを抽出するクラスのインターフェース
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "ITextFileReader.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class JsonParser;

/*!
 @class     IPreviousDataReader
 @brief
 ptsとインターフェースクラスが生成したPreviousTask_x.jsonファイルを読み込み、メトリックス取得に必要なデータを抽出するクラスのインターフェース
*/
class IPreviousDataReader
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  IPreviousDataReader() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~IPreviousDataReader() = default;

  /*!
   @brief          指定されたプロジェクトに定義されているSprint情報を収集する
   @param[in]      projectId 収集したいプロジェクト
   @return         スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）
  */
  virtual std::list<std::map<std::string, std::string>> preparePreviousTaskData(const measurementor::ProjectId& projectId) = 0;
};

}  // namespace measurementor
