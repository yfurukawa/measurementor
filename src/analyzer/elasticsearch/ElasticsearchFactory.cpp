#include <new>
#include "ElasticsearchFactory.h"

namespace measurementor
{

IAnalyzerFactory* IAnalyzerFactory::getInstance()
{
    static analyzer::ElasticsearchFactory theFactory;
    if( analyzer::ElasticsearchFactory::isDestroyed() ) {
        (void) new (&theFactory) analyzer::ElasticsearchFactory;
    }
    return &theFactory;
}

}

namespace analyzer {

bool ElasticsearchFactory::destroyed_ = false;

ElasticsearchFactory::~ElasticsearchFactory()
{
    if( destroyed_ == false ) {
        if( analyzer_ != nullptr )
        {
            delete analyzer_;
            analyzer_ = nullptr;
        }
        destroyed_ = true;
    }
}

}