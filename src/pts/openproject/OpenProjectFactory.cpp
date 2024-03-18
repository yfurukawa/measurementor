#include <new>
#include "OpenProjectFactory.h"

namespace measurementor
{

IPtsFactory* IPtsFactory::getInstance()
{
    static pts::OpenProjectFactory theFactory;
    if( pts::OpenProjectFactory::isDestroyed() ) {
        (void) new (&theFactory) pts::OpenProjectFactory;
    }
    return &theFactory;
}

}

namespace pts {

bool OpenProjectFactory::destroyed_ = false;

OpenProjectFactory::~OpenProjectFactory()
{
    if( destroyed_ == false ) {
        if( pts_ != nullptr )
        {
            delete pts_;
            pts_ = nullptr;
        }
        destroyed_ = true;
    }
}

}