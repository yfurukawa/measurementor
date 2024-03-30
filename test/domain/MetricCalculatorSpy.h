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

  std::map<TaskId, nlohmann::json> getDurationDataList();
};

}  // namespace measurementor
