/*!
 @file  ReworkRepositoryFactory.cpp
 @copyright Copyright 2024 yoshihiro Furukawa
*/
#include "ReworkRepositoryFactory.h"
#include <new>

namespace measurementor
{

IReworkRepositoryFactory* IReworkRepositoryFactory::getInstance()
{
  static repository::ReworkRepositoryFactory theFactory;
  if (repository::ReworkRepositoryFactory::isDestroyed())
  {
    (void)new (&theFactory) repository::ReworkRepositoryFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace repository
{

bool ReworkRepositoryFactory::destroyed_ = false;

ReworkRepositoryFactory::~ReworkRepositoryFactory()
{
  if (destroyed_ == false)
  {
    if (repository_ != nullptr)
    {
      delete repository_;
      repository_ = nullptr;
    }
    destroyed_ = true;
  }
}

}  // namespace repository
