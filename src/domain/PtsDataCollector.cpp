#include "PtsDataCollector.h"
#include "../pts/OpenProjectFactory.h"
#include "../pts/OpenProject.h"

namespace measurementor
{

void PtsDataCollector::correctData()
{
    pts::OpenProjectFactory::getInstance()->createPts()->collectAllActiveProject();
}

}