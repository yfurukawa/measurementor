/*!
 @file      IRepository.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスの抽象
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
   @brief     タスクがIn Progress状態に移行した日時を登録する
   @param[in] taskId 登録対象タスクのID
   @param[in] updatedAt 移行した日時
  */
  virtual registerInProgressStartDate(TaskId taskId, UpdatedAt updateAt) = 0;

  /*!
   @brief     タスクがIn Progress状態に移行した日付を取得する
   @param[in] taskId 取得対象タスクのID 
   @return    In Progress状態に移行した日時
  */
  virtual UpdateAt getInProgressStartedDate(TasjId taskId) = 0;

protected:
};

}  // namespace measurementor
