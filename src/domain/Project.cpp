#include "Project.h"

namespace measurementor
{

Project::Project( Id id, Name name, ParentId parentId )
    : id_(id),
    name_(name),
    parentId_(parentId),
    point_(0)    
{
    childProjects_.clear();
}

void Project::relateChildProject( Id childProjectId )
{
    childProjects_.emplace_back( childProjectId );
}

}