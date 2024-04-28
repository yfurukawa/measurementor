/*!
 @file      MetricCalculator.h
 @brief     Taskの前回値と今回値を比較し、メトリクスをとる
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include "Chronos.h"
#include "ReworkCounter.h"
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
  IRepository* repository_;                                   //!< メトリックスデータの中間データを永続化するリポジトリ
  std::unique_ptr<::Chronos> chronos_;                        //!< 時刻操作を提供するクラス
  IAnalyzer* analyzer_;                                       //!< 計測データを分析するシステムとインターフェースするクラス
  std::unique_ptr<ReworkCounter> reworkCounter_;              //!< 手戻り回数を集計するクラス
  std::map<TaskId, std::shared_ptr<Task>> currentTaskList_;   //!< 現在値を保持しているタスクのリスト
  std::map<TaskId, std::shared_ptr<Task>> previousTaskList_;  //!< 前回値を保持しているタスクのリスト
  std::map<TaskId, nlohmann::json> durationDataList_;         //!< 各タスクの作業期間データ

  /*!
   @brief  In-Progress, ReviewおよびTaskを完了するまでに掛かった時間を計算する
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask, std::string timestamp);

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
   @brief      データ取得の１間隔内で複数の状態遷移があったタスクを処理する
   @param[in]  currentTask  対象のタスク
   @param[in]  timestamp  当該処理をした日時。（elasticsearchで使用する）
   @note       前回値データが無いタスクがこの処理の対象と仮定している
  */
  void handlingSkippedState(std::shared_ptr<Task> currentTask, std::string timestamp);

  /*!
   @brief  ある状態に留まっていた時間を計算する
   @param[in] startDate  期間の開始日時
   @param[in] endData    期間の終了日時
   @return    滞留時間[H]
   @note  滞留時間は0.25[H]間隔。日にちを跨いだら、１７時から翌朝８時まではカウントしない。また、週末の土日は考慮するが、祝日は考慮しない。
  */
  double calculateDuration(::ISO8601String startDate, ::ISO8601String endDate);

  /*!
   @brief  小数点以下の時間を0.25[H]毎に丸める
   @param[in]  decimal 小数点以下の時間
   @return  丸めた時間
   @note しきい値を1秒でも超えたら15分を超えたとみなす。<br>
        1秒 -> 0.25H<br>
        15分1秒 -> 0.5H
  */
  double roundDecimal(double decimal);

  /*!
   @brief  start/endの経過日数を算出する
   @param[in] startDate  期間の開始日時
   @param[in] endData    期間の終了日時
   @return  経過日数
  */
  std::uint_fast32_t passedDays(::ISO8601String startDate, ::ISO8601String endDate);

  /*!
   @brief  週末の回数を算出する
   @param[in] startDate  期間の開始日時
   @param[in] endData    期間の終了日時
   @return 経過した週末の回数
  */
  std::uint_fast16_t passedWeekends(::ISO8601String startDate, ::ISO8601String endDate);

};

}  // namespace measurementor
