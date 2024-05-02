/*!
 @file      ReworkCounter.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "IReworkRepository.h"
#include "IReworkRepositoryFactory.h"
#include "ReworkCounter.h"

namespace measurementor
{

ReworkCounter::ReworkCounter()
  : reworkRepository_(IReworkRepositoryFactory::getInstance()->createRepository())
{
}

void ReworkCounter::occurRework(TaskId taskId, UpdatedAt reworkStartDate)
{
  // 指定されたTaskが初めての手戻りであれば新規に手戻り情報を登録する。
  auto result = reworkRepository_->getReworkTimes(taskId);
  if (result)
  {
    ReworkTimes reworkTimes(result.value());
    ReworkTimes const one = ReworkTimes{1};
    reworkTimes = reworkTimes + one;
    reworkRepository_->storeNewReworkTimes(taskId, reworkTimes);
  }
  else
  {
    reworkRepository_->registerReworkedTask(taskId, reworkStartDate);
  }
}

ReworkTimes ReworkCounter::completeTask(TaskId taskId)
{
  // 指定されたTaskの手戻り回数情報が無かった場合は、手戻り回数を0と回答する
  auto result = reworkRepository_->getReworkTimes(taskId);
  if (result)
  {
    ReworkTimes reworkTimes(result.value());
    return reworkTimes;
  }
  else
  {
    ReworkTimes reworkTimes(0);
    return reworkTimes;
  }
  
}

}  // namespace measurementor