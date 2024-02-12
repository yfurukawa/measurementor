#include <chrono>
#include "Chronos.h"
#include "ToISO8601String.hpp"
#include "FromISO8601String.hpp"

std::time_t Chronos::now() const
{
    return Clock::to_time_t( Clock::now() );
}

std::string Chronos::nowIso8601BasicGmt() const
{
    std::regex date("-");
    std::regex time(":");

    std::string extendedString( toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>());
    std::string s1 = std::regex_replace( extendedString, date, "");
    std::string s2 = std::regex_replace( s1, time, "" );
    return s2;
}

std::string Chronos::nowIso8601ExtendedGmt() const
{
    return toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>();
}

std::string Chronos::nowIso8601BasicGmt() const
{
    std::regex date("-");
    std::regex time(":");

    std::string extendedString( toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>());
    std::string s1 = std::regex_replace( extendedString, date, "");
    std::string s2 = std::regex_replace( s1, time, "" );
    return s2;
}

std::string Chronos::nowIso8601ExtendedGmt() const
{
    return toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>();
}
