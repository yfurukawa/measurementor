/*!
 @file      MetricCalculatorSpy.h
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include "../../src/domain/MetricCalculator.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Task;

/*!
 @class     MetricCalculatorSpy
 @brief     Taskの前回値と今回値を比較し、メトリクスをとる
*/
class MetricCalculatorSpy : public MetricCalculator
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  MetricCalculatorSpy() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~MetricCalculatorSpy() = default;

  /*!
   @brief  メトリックを計算する
   @param[in] currentTaskList  現在値を保持しているタスクリスト
   @param[in] previousTaskList  前回値を保持しているタスクリスト
  */
  void calculateMetrics(std::map<TaskId, std::shared_ptr<Task>> currentTaskList, std::map<TaskId, std::shared_ptr<Task>> previousTaskList);

  /*!
   @brief  In-Progress, ReviewおよびTaskを完了するまでに掛かった時間を計算する
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void checkTransit(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask, std::string timestamp);
  
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
   @brief  週末の回数を算出する
   @param[in] startDate  期間の開始日時
   @param[in] endData    期間の終了日時
   @return 経過した週末の回数
  */
  std::uint_fast16_t passedWeekends(::ISO8601String startDate, ::ISO8601String endDate);

  std::map<TaskId, nlohmann::json> getDurationDataList();
};

}  // namespace measurementor
