/*!
 @file      MetricCalculator.h
 @brief     Taskの前回値と今回値を比較し、メトリクスをとる
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include "Chronos.h"
#include "domainPrimitives/MeasurementPrimitives.h"
#include "nlohmann/json.hpp"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Task;
class IAnalyzer;
class IRepository;

/*!
 @class     MetricCalculator
 @brief     Taskの前回値と今回値を比較し、メトリクスをとる
*/
class MetricCalculator
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  MetricCalculator();

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~MetricCalculator() = default;

  /*!
   @brief  メトリックを計算する
   @param[in] currentTaskList  現在値を保持しているタスクリスト
   @param[in] previousTaskList  前回値を保持しているタスクリスト
  */
  void calculateMetrics(std::map<TaskId, std::shared_ptr<Task>> currentTaskList, std::map<TaskId, std::shared_ptr<Task>> previousTaskList);

protected:
  IRepository* repository_;  //!< メトリックスデータの中間データを永続化するリポジトリ
  std::unique_ptr<::Chronos> chronos_;  //!< 時刻操作を提供するクラス
  IAnalyzer* analyzer_;                 //!< 計測データを分析するシステムとインターフェースするクラス
  std::map<TaskId, std::shared_ptr<Task>> currentTaskList_;   //!< 現在値を保持しているタスクのリスト
  std::map<TaskId, std::shared_ptr<Task>> previousTaskList_;  //!< 前回値を保持しているタスクのリスト
  std::map<TaskId, nlohmann::json> durationDataList_;          //!< 各タスクの作業期間データ

  /*!
   @brief  In-Progress, ReviewおよびTaskを完了するまでに掛かった時間を計算する
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask);

  /*!
   @brief  NewからIn-Progressに移行した際の中間データ更新処理をする
   @param[in] updateData  メトリックスの中間データ
   @param[in] previousTask  前回値を保持しているタスク
  */
  void transitFromNewToInProgress(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask);

  /*!
   @brief  In-ProgressからReviewに移行した際の中間データ更新処理をする
   @param[in] updateData  メトリックスの中間データ
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void transitFromInProgressToReview(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask);

  /*!
   @brief  ReviewからCloseに移行した際の中間データ更新処理をする
   @param[in] updateData  メトリックスの中間データ
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void transitFromReviewToClose(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask);

  /*!
   @brief  In-ProgressからCloseに移行した際の中間データ更新処理をする
   @param[in] updateData  メトリックスの中間データ
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void transitFromInProgressToClose(nlohmann::json& updateData, std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask);

  /*!
   @brief  ある状態に留まっていた時間を計算する
   @param[in] startDate  期間の開始日時
   @param[in] endData    期間の終了日時
   @return    滞留時間[H]
   @note  滞留時間は0.25[H]間隔。日にちを跨いだら、１７時から翌朝８時まではカウントしない。また、週末の土日は考慮するが、祝日は考慮しない。
  */
  double calculateDuration(::ISO8601String startDate, ::ISO8601String endDate);
};

}  // namespace measurementor
