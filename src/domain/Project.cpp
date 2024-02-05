#include "Project.h"

namespace measurementor
{

Project::Project( Id id, Name name )
 : id_(id), name_(name), point_(0)
{
    childProjects_.clear();
}

void Project::relateChildProject( Id childProjectId )
{
    childProjects_.emplace_back( childProjectId );
}

}