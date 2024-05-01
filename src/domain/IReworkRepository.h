/*!
 @file      IReworkRepository.h
 @brief     手戻り回数の集計値やその元データを保持するRepositoryクラスの抽象
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     IReworkRepository
 @brief     手戻り回数の集計値やその元データを保持するRepositoryクラスの抽象
 @details   本クラスは、手戻り回数の集計値やその元データを永続化し提供するクラスの抽象である。
*/
class IReworkRepository
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  IReworkRepository() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~IReworkRepository() = default;

  /*!
   @brief       手戻り回数を返す
   @param[in]   taskId  対象TaskのId
   @return      手戻り回数
   @note        対象のTaskのデータが無い（初めての手戻り）場合は、nulloptを返す
  */
  virtual std::optional<ReworkTimes> getReworkTimes(TaskId taskId) = 0;

  /*!
   @brief     手戻りがあったタスクを新規登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] reworkStartDate  手戻りにより再びIn Progressに戻った日時
  */
  virtual void registerReworkedTask(TaskId taskId, UpdatedAt reworkStartDate) = 0;

  /*!
   @brief     タスクがIn Progress状態に戻った日時を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    In Progress状態に移行した日時
   @note      対象タスクの日時が登録されていない場合、std::nulloptが返される
  */
  virtual std::optional<UpdatedAt> getStartDateOnInProgress(TaskId taskId) = 0;

  /*!
   @brief     タスクがReview状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    Review状態に移行した日時
   @note      対象タスクの日時が登録されていない場合、std::nulloptが返される
  */
  virtual std::optional<UpdatedAt> getStartDateOnReview(TaskId taskId) = 0;

  /*!
   @brief     タスクの手戻り情報を削除する
   @param[in] taskId 削除対象タスクのID
  */
  virtual void deleteReworkedTask(TaskId taskId) = 0;

protected:
};

}  // namespace measurementor
