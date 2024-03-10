#include "Index.h"

namespace analyzer
{

analyzer::Index::Index(std::string index)
    : index_ (index )
{
}

std::string analyzer::Index::get() const
{
    return index_;
}

void analyzer::Index::convertCharactor()
{
}

}
