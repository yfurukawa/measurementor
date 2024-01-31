#include "Chronos.h"

std::time_t Chronos::now() const
{
    return Clock::to_time_t( Clock::now() );
}
