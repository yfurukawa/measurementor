/*!
 @file  RepositoryMockFactory.cpp
 @copyright Copyright 2024 yoshihiro Furukawa
*/
#include "RepositoryMockFactory.h"
#include <new>

namespace measurementor
{

IRepositoryFactory* IRepositoryFactory::getInstance()
{
  static repository::RepositoryMockFactory theFactory;
  if (repository::RepositoryMockFactory::isDestroyed())
  {
    (void)new (&theFactory) repository::RepositoryMockFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace repository
{

bool RepositoryMockFactory::destroyed_ = false;

RepositoryMockFactory::~RepositoryMockFactory()
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
