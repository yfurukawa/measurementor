/*!
 @file      PreviousDataReader.h
 @brief     OpenProjectクラスが生成したPreviousTask_x.jsonファイルを読み込み、メトリックス取得に必要なデータを抽出する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "DomainPrimitivesForOpenProject.h"
#include "ITextFileReader.h"
#include "../../domain/domainPrimitives/MeasurementPrimitives.h"
#include "../../domain/IPreviousDataReader.h"

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------
class JsonParser;

/*!
 @class     PreviousDataReader
 @brief     OpenProjectクラスが生成したPreviousTask_x.jsonファイルを読み込み、メトリックス取得に必要なデータを抽出する
*/
class PreviousDataReader final : public measurementor::IPreviousDataReader
{
private :
  /*!
   @brief  デフォルトコンストラクタ
  */
  PreviousDataReader() = delete;

public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  explicit PreviousDataReader(std::unique_ptr<::ITextFileReader> fileReader);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~PreviousDataReader() = default;

  /*!
   @brief          指定されたプロジェクトに定義されているSprint情報を収集する
   @param[in]      project 収集したいプロジェクト
   @return         スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）
  */
  std::list<std::map<std::string, std::string>> preparePreviousTaskData(const measurementor::ProjectId& projectId) override;

private:
  std::unique_ptr<::ITextFileReader>
    previousDataReader_;  //!< OpenProjectのサーバから取得したJsonオブジェクトをファイルに保存しておくためのWriter
  std::unique_ptr<JsonParser> jsonParser_;  //!< Jsonオブジェクトのパーサ
};

}  // namespace pts
