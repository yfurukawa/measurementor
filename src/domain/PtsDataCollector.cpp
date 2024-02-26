#include "PtsDataCollector.h"
#include "../pts/openproject/OpenProjectFactory.h"   // TODO
#include "../pts/openproject/OpenProject.h"          // TODO

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

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        ptsFactory_->createPts()->collectSprintInformationOf( project->second );
    }

    this->aggrigateData();
}

void PtsDataCollector::aggrigateData()
{
    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateStoryPointsInPBL();
    }

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateStoryPointsInProgress();
    }

    for( auto project = begin(projectList_); project != end(projectList_); ++project )
    {
        project->second->aggrigateRemainingWorkTime();
    }
}

}