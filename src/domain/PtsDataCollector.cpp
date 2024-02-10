#include "PtsDataCollector.h"
#include "../pts/OpenProjectFactory.h"
#include "../pts/OpenProject.h"

#include <iostream>

namespace measurementor
{

PtsDataCollector::PtsDataCollector() : ptsFactory_( PtsFactory::getInstance() )
{
    projectList_.clear();
}

PtsDataCollector::~PtsDataCollector()
{
    projectList_.clear();
    ptsFactory_->~PtsFactory();
}

void PtsDataCollector::correctData()
{
     ptsFactory_->createPts()->collectAllActiveProject( projectList_ );

    for( auto p = projectList_.begin(); p != projectList_.end(); ++p )
    {
        std::cout << p->first << " : " << p->second->name() << std::endl;
        if( p->second->hasChild() )
            p->second->printChild();
    }

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        ptsFactory_->createPts()->collectSprintInformationOf( project->second );
    }
   
}

}