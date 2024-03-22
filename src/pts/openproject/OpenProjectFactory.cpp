/*!
 @file  OpenProjectFactory.cpp
 @copyright Copyright 2024 yoshihiro Furukawa
*/
#include "OpenProjectFactory.h"
#include <new>

namespace measurementor
{

IPtsFactory* IPtsFactory::getInstance()
{
  static pts::OpenProjectFactory theFactory;
  if (pts::OpenProjectFactory::isDestroyed())
  {
    (void)new (&theFactory) pts::OpenProjectFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace pts
{

bool OpenProjectFactory::destroyed_ = false;

OpenProjectFactory::~OpenProjectFactory()
{
  if (destroyed_ == false)
  {
    if (pts_ != nullptr)
    {
      delete pts_;
      pts_ = nullptr;
    }
    destroyed_ = true;
  }
}

}  // namespace pts
