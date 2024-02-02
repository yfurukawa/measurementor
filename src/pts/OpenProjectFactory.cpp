#include <new>
#include "OpenProjectFactory.h"

namespace measurementor
{

PtsFactory* PtsFactory::getInstance()
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
    delete pts_;
    destroyed_ = true;
}

}