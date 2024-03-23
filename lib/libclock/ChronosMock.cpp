/*!
 @file      ChronosMock.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <regex>
#include "ChronosMock.h"

std::time_t ChronosMock::now() const
{
  return returnTime_t_;
}

std::string ChronosMock::nowIso8601BasicGmt() const
{
  return returnDateTimeGMT_.get();
}

std::string ChronosMock::nowIso8601ExtendedGmt() const
{
  return returnDateTimeGMT_.get();
}

std::string ChronosMock::nowIso8601Basic() const
{
  return returnDateTimeLT_.get();
}

std::string ChronosMock::nowIso8601Extended() const
{
  return returnDateTimeLT_.get();
}

std::time_t ChronosMock::convertToTime_t(ISO8601String iso8601String)
{
  return returnTime_t_;
}
