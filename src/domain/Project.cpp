#include "Project.h"

namespace measurementor
{

Project::Project( Id id, Name name )
 : id_(id), name_(name), point_(0)
{
    childProjects_.clear();
}

void Project::addChildProject( Id childProjectId, std::shared_ptr<Project> childProject )
{
    childProjects_.insert( std::make_pair( childProjectId.get(), childProject ) );
}

}