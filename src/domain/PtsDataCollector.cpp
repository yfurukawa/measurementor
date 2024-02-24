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

    // データ収集後にプロジェクトツリーを表示する（確認用）
    for( auto p = projectList_.begin(); p != projectList_.end(); ++p )
    {
        std::cout << p->first << " : " << p->second->name() << std::endl;
        if( p->second->hasChild() )
            p->second->printChild();
    }
}

}