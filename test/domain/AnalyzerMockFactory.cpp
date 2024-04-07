/*!
 @file AnalyzerMockFactory.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <new>
#include "AnalyzerMockFactory.h"

namespace measurementor
{

IAnalyzerFactory* IAnalyzerFactory::getInstance()
{
  static analyzer::AnalyzerMockFactory theFactory;
  if (analyzer::AnalyzerMockFactory::isDestroyed())
  {
    (void)new (&theFactory) analyzer::AnalyzerMockFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace analyzer
{

bool AnalyzerMockFactory::destroyed_ = false;

AnalyzerMockFactory::~AnalyzerMockFactory()
{
  if (destroyed_ == false)
  {
    if (analyzer_ != nullptr)
    {
      delete analyzer_;
      analyzer_ = nullptr;
    }
    destroyed_ = true;
  }
}

}  // namespace analyzer