/*!
 @file  PreviousDataReaderFactory.cpp
 @copyright Copyright 2024 yoshihiro Furukawa
*/
#include "PreviousDataReaderFactory.h"
#include <new>

namespace measurementor
{

IPreviousDataReaderFactory* IPreviousDataReaderFactory::getInstance()
{
  static pts::PreviousDataReaderFactory theFactory;
  if (pts::PreviousDataReaderFactory::isDestroyed())
  {
    (void)new (&theFactory) pts::PreviousDataReaderFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace pts
{

bool PreviousDataReaderFactory::destroyed_ = false;

PreviousDataReaderFactory::~PreviousDataReaderFactory()
{
  if (destroyed_ == false)
  {
    if (previousDataReader_ != nullptr)
    {
      delete previousDataReader_;
      previousDataReader_ = nullptr;
    }
    destroyed_ = true;
  }
}

}  // namespace pts
