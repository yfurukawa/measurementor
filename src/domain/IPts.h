/*!
 @file      IPts.h
 @brief     PTSとインターフェースするクラスの抽象
 @copyright Copyright 2024 Yoshihiro Furukawa
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
 @class     IPts
 @brief     PTSとインターフェースするクラスの抽象
 @note      本クラスは、Project Tracking System (PTS) からプロジェクトの情報を取得し、メトリックスの算出ができるように
 加工するクラスのための抽象クラスである。
*/
class IPts
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  IPts() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~IPts() = default;

  /*!
   @brief   全てのアクティブプロジェクトを収集する
   @note    本メソッドは、PTS（Project Tracking System）で管理されているプロジェクトの内、
            現在アクティブなものを収集する。また、プロジェクトは、複数の子プロジェクトを有する可能性がある。
            親プロジェクトは、子プロジェクトのみを有し、スプリント等の管理データは末端のプロジェクトのみが有すると想定している。
   @return  アクティブプロジェクトのリスト（Projectの情報マップ（情報名、値）をリスト化したもの）<br>
            マップの詳細は、<br>
            キー         ｜ 値<br>
            projectId   ｜ PTSで付番されたプロジェクト識別番号<br>
            projectName ｜ プロジェクトの名称<br>
            parentId    ｜ （入れ子になっている場合の）親プロジェクトの識別番号
  */
  virtual std::list<std::map<std::string, std::string>> collectAllActiveProject() = 0;

  /*!
   @brief       指定されたプロジェクトに定義されているSprint情報を収集する
   @param[in]   projectId 収集したいSprintを有するプロジェクトの識別番号
   @return      スプリントのリスト（Sprintの情報マップ（情報名、値）をリスト化したもの）<br>
                マップの詳細は、<br>
                キー ｜ 値<br>
                sprintId ｜ Sprintの識別番号<br>
                projectId ｜ このSprintを持つプロジェクトの識別番号<br>
                sprintName ｜ Sprintの名称<br>
                status ｜ Sprintの状態（Open／Close）を表す<br>
                startDate ｜ Sprint期間の開始日<br>
                endDate ｜ Sprint期間の終了日<br>
  */
  virtual std::list<std::map<std::string, std::string>> collectSprintInformation(const measurementor::ProjectId& projectId) = 0;

  /*!
   @brief       指定されたプロジェクトに定義されているItemの情報を収集する
   @param[in]   projectId 収集したいItemを有するプロジェクトの識別番号
   @return      プロダクトバックログアイテムのリスト（PBIの情報マップ（情報名、値）をリスト化したもの）<br>
                マップの詳細は、<br>
                キー ｜ 値<br>
                itemId ｜ このItem（プラダクトバックログアイテム）の識別番号<br>
                itemName ｜ Itemの名称（内容）
                projectId ｜ このItemを持つプロジェクトの識別番号<br>
                sprintId ｜ このItemが割り当てられたSprintの識別番号。プロダクトバックログに積まれている（Sprintに未割り当て）場合は、0になる。
                storyPoint ｜ 見積もられたポイント数
                status ｜ Itemの状態（Open／Close）<br>
                statusCode ｜ Itemの状態の識別番号（Open： ／Close： ）<br>
                totalEstimatedTime ｜ このItemが有する未完了タスクの総見積時間[H]。結果的に残作業時間となる。
  */
  virtual std::list<std::map<std::string, std::string>> collectItemInformation(const measurementor::ProjectId& projectId) = 0;

  /*!
   @brief       指定されたプロジェクトに定義されているTaskの情報を収集する
   @param[in]   projectId 収集したいプロジェクト
   @return      タスクのリスト（タスクの情報マップ（情報名、値）をリスト化したもの）<br>
                マップの詳細は、<br>
                キー ｜ 値<br>
                taskId ｜ タスクの識別番号<br>
                taskName ｜ タスクの名称（内容）<br>
                itemId ｜ このTaskを持つItemの識別番号<br>
                projectId ｜ このTeskを持つプロジェクトの識別番号<br>
                sprintId ｜ このTaskを持つItemが割り当てられたSprintの識別番号。<br>
                author ｜ このTaskを出したメンバ名<br>
                estimatedTime ｜ このタスクの見積時間[H]<br>
                assignee ｜ Taskの担当者<br>
                status ｜ Taskの状態（New、In Progress、Review、Close）<br>
                statusCode ｜ Taskの状態の識別番号（New ： 1、In Progress ： 7、Review ： 15、Close ： 12）<br>
                updatedAt ｜ Taskが更新された日時（ISO8601形式のローカルタイム）
  */
  virtual std::list<std::map<std::string, std::string>> collectTaskInformation(const measurementor::ProjectId& projectId) = 0;

protected:
};

}  // namespace measurementor
