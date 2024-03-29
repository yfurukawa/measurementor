/*!
 @file      Project.h
 @brief     プロジェクトデータ
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "JsonCreator.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Sprint;
class Item;

/*!
 @class     Project
 @brief     プロジェクトデータ
 @note      本クラスは、Project Tracking System (PTS)
 から取得したプロジェクトの情報の内、メトリックスの算出に必要となるデータを保持するものである。<br>
 又、PTS内ではプロジェクトが子プロジェクトを持つことが想定されるため、その状況にも対応可能にしておく。
*/
class Project final
{
private:
  /*!
   @brief  デフォルトコンストラクタ
  */
  Project() = delete;

public:
  /*!
   @brief  コンストラクタ
   @param[in]  projectId    このProjectのID
   @param[in]  projectName  このProjectの名称
   @param[in]  parentId     このProjectの親ProjectのID（親が無ければ0）
   @param[in]  timestamp    elasticserchに登録する際に使用する日時（ISO8601の拡張型GMT形式）
  */
  Project(ProjectId projectId, Name projectName, ProjectId parentId, Timestamp timestamp);

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~Project() = default;

  /*!
   @brief      自身の情報からJSONオブジェクトを生成して返す
   @return     JSONオブジェクト（文字列）
  */
  std::string createJson();

  /*!
   @brief      残りのユーザーストーリーポイントを登録する
   @param[in]  remainingStoryPint  プロジェクト毎に集計した残ユーザーストーリーポイント
  */
  void registerStoryPoint(Point remainingStoryPint);

private:
  const ProjectId projectId_;  //!< Project ID
  const Name name_;            //!< Project名称
  const ProjectId parentId_;   //!< 親のID
  const Timestamp timestamp_;  //!< elasticserchに登録する際に使用する日時（ISO8601の拡張型GMT形式）
  Point remaingStoryPoints_;   //!< Product Back Logに残っているユーザストーリーの総ポイント数
  JsonCreator jsonCreator_;    //!< JSON Objectを生成するクラスのインスタンス
};

}  // namespace measurementor
