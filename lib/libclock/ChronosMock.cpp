#include <regex>
#include "ChronosMock.h"
#include "ToISO8601String.hpp"
#include "FromISO8601String.hpp"

ChronosMock::ChronosMock( std::string iso8601String )
    : returnDateTime_(std::move(iso8601String)),
    returnTime_t_( ToTimeT(iso8601String) )
{
}

std::time_t ChronosMock::now() const
{
    return returnTime_t_;
}

std::string ChronosMock::nowIso8601BasicGmt() const
{
    std::regex date("-");
    std::regex time(":");

    std::string extendedString( toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>( std::chrono::system_clock::from_time_t( returnTime_t_ ) ));
    std::string s1 = std::regex_replace( extendedString, date, "");
    std::string s2 = std::regex_replace( s1, time, "" );
    return s2;
}

std::string ChronosMock::nowIso8601ExtendedGmt() const
{
    return toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>( std::chrono::system_clock::from_time_t( returnTime_t_ ) );
}

std::string ChronosMock::nowIso8601Basic() const
{
    std::regex date("-");
    std::regex time(":");

    std::string extendedString( toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>( std::chrono::system_clock::from_time_t( returnTime_t_ ) ));
    std::string s1 = std::regex_replace( extendedString, date, "");
    std::string s2 = std::regex_replace( s1, time, "" );
    return s2;
}

std::string ChronosMock::nowIso8601Extended() const
{
    return toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>( std::chrono::system_clock::from_time_t( returnTime_t_ ));
}

std::time_t ChronosMock::convertToTime_t( std::string iso8601String )
{
    return ToTimeT( iso8601String );
}
