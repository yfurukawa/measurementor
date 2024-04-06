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
  std::map<TaskId, std::shared_ptr<Task>> currentTaskList_;   //!< 現在値を保持しているタスクのリスト
  std::map<TaskId, std::shared_ptr<Task>> previousTaskList_;  //!< 前回値を保持しているタスクのリスト
  std::map<TaskId, nlohmann::json> durationDataList_;          //!< 各タスクの作業期間データ

  /*!
   @brief  In-Progress, ReviewおよびTaskを完了するまでに掛かった時間を計算する
   @param[in] currentTask  現在値を保持しているタスク
   @param[in] previousTask  前回値を保持しているタスク
  */
  void calculateDuration(std::shared_ptr<Task>& currentTask, std::shared_ptr<Task>& previousTask);
};

}  // namespace measurementor
