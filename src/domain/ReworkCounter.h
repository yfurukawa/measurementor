/*!
 @file      ReworkCounter.h
 @brief     Taskの手戻り回数を集計する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------

namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     ReworkCounter
 @brief     Taskの手戻り回数を集計する
 @details   本クラスは、Taskの状態が、ReviewからIn Progressに戻った場合に、「手戻り」が発生したとして当該Taskの手戻り回数をインクリメントする。
 手戻り回数については、一時的にデータベースに保存し、それを使用する。最終的にTaskがCloseされた段階で分析システムにデータを登録する。
*/
class ReworkCounter
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  ReworkCounter() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~ReworkCounter() = default;

  /*!
   @brief      手戻りが発生したTaskの手戻り回数をインクリメントする
   @param[in]  taskId 手戻りが発生したTaskのID
  */
  void occurRework(TaskId taskId);
};

}