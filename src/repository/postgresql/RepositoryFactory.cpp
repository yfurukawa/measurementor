/*!
 @file  RepositoryFactory.cpp
 @copyright Copyright 2024 yoshihiro Furukawa
*/
#include "RepositoryFactory.h"
#include <new>

namespace measurementor
{

IRepositoryFactory* IRepositoryFactory::getInstance()
{
  static repository::RepositoryFactory theFactory;
  if (repository::RepositoryFactory::isDestroyed())
  {
    (void)new (&theFactory) repository::RepositoryFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace repository
{

bool RepositoryFactory::destroyed_ = false;

RepositoryFactory::~RepositoryFactory()
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
