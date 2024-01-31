#include "ChronosMock.h"

std::time_t ChronosMock::now() const
{
    std::time_t dummy(1703209792);
    return dummy;
}
