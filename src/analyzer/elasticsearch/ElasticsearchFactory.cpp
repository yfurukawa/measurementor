/*!
 @file ElasticsearchFactory.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <new>
#include "ElasticsearchFactory.h"

namespace measurementor
{

IAnalyzerFactory* IAnalyzerFactory::getInstance()
{
  static analyzer::ElasticsearchFactory theFactory;
  if (analyzer::ElasticsearchFactory::isDestroyed())
  {
    (void)new (&theFactory) analyzer::ElasticsearchFactory;
  }
  return &theFactory;
}

}  // namespace measurementor

namespace analyzer
{

bool ElasticsearchFactory::destroyed_ = false;

ElasticsearchFactory::~ElasticsearchFactory()
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