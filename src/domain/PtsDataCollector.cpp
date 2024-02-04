#include <list>
#include "PtsDataCollector.h"
#include "../pts/OpenProjectFactory.h"
#include "../pts/OpenProject.h"

namespace measurementor
{

PtsDataCollector::PtsDataCollector()
{
    projectList_.clear();
}

void PtsDataCollector::correctData()
{
    
    pts::OpenProjectFactory::getInstance()->createPts()->collectAllActiveProject( projectList_ );
}

}