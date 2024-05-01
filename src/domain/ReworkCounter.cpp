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
  auto reworkTimes = reworkRepository_->getReworkTimes(taskId);
  if (reworkTimes)
  {
    auto const one = ReworkTimes{1};
    reworkTimes.value() = reworkTimes.value() + one;
  }
  else
  {
    reworkRepository_->registerReworkedTask(taskId, reworkStartDate);
  }
}

}  // namespace measurementor