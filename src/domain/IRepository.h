/*!
 @file      IRepository.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスの抽象
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include "nlohmann/json.hpp"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     IRepository
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスの抽象
 @note      本クラスは、メトリックスの計算値やその元データを永続化し提供するクラスの抽象である。
*/
class IRepository
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  IRepository() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~IRepository() = default;


  /*!
   @brief     タスクのメトリックスを登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] metricsData json形式にしたメトリックスデータ
  */
  virtual void registerMetricsData(TaskId taskId, nlohmann::json metricsData) = 0;

  /*!
   @brief     タスクがIn Progress状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    nlohmann::json メトリックスデータ
  */
  virtual std::optional<UpdatedAt> getStarDateOnInProgress(TaskId taskId) = 0;

  /*!
   @brief     タスクがReview状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    nlohmann::json メトリックスデータ
  */
  virtual std::optional<UpdatedAt> getStarDateOnReview(TaskId taskId) = 0;

  /*!
   @brief     タスクがClose状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    nlohmann::json メトリックスデータ
   TODO 不要なメソッドかも
  */
  virtual std::optional<UpdatedAt> getStarDateOnClose(TaskId taskId) = 0;

  /*!
   @brief     InProgressのDurationを取得する
   @param[in] taskId 取得対象タスクのID 
   @return    時間[H]
  */
  virtual long getInProgressDuration(TaskId taskId) = 0;

  /*!
   @brief     タスクのメトリックスを更新する
   @param[in] taskId 更新対象タスクのID
   @param[in] metricsData json形式にしたメトリックスデータ
  */
  virtual void updateMetricsData(TaskId taskId, nlohmann::json metricsData) = 0;

  /*!
   @brief     タスクのメトリックスを削除する
   @param[in] taskId 削除対象タスクのID
  */
  virtual void deleteMetricsData(TaskId taskId) = 0;

protected:
};

}  // namespace measurementor
