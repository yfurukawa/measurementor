/*!
 @file      Chronos.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <chrono>
#include <cstdint>
#include <regex>
#include <sstream>
#include "Chronos.h"

std::time_t Chronos::now() const
{
  return Clock::to_time_t(Clock::now());
}

std::string Chronos::nowIso8601BasicGmt() const
{
  std::regex date("-");
  std::regex time(":");

  std::string extendedString(
    timeProvider_->toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>());
  std::string s1 = std::regex_replace(extendedString, date, "");
  std::string s2 = std::regex_replace(s1, time, "");
  return s2;
}

std::string Chronos::nowIso8601ExtendedGmt() const
{
  return timeProvider_->toString_iso8601_gmt<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>();
}

std::string Chronos::nowIso8601Basic() const
{
  std::regex date("-");
  std::regex time(":");

  std::string extendedString(timeProvider_->toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>());
  std::string s1 = std::regex_replace(extendedString, date, "");
  std::string s2 = std::regex_replace(s1, time, "");
  return s2;
}

std::string Chronos::nowIso8601Extended() const
{
  return timeProvider_->toString_iso8601<std::chrono::high_resolution_clock::time_point, std::chrono::microseconds>();
}

std::time_t Chronos::convertToTime_t(ISO8601String iso8601String)
{
  std::string time(iso8601String.get());
  struct tm iso8601Time;
  std::smatch elements;
  std::int_fast64_t gmtoffset(0);
  std::regex iso8601Basic(
    "([0-9]{4})([01][0-9])([0-3][0-9])T([0-2][0-9])([0-5][0-9])([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2})([0-9]{2}))?");
  std::regex iso8601Extended(
    "([0-9]{4})-([01][0-9])-([0-3][0-9])T([0-2][0-9]):([0-5][0-9]):([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2}):([0-9]{2}))?");

  if (std::regex_match(time, elements, iso8601Basic))
  {
    unsigned int mon = std::stoi(elements[2].str());
    if (1 > mon || 12 < mon)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int mday = std::stoi(elements[3].str());
    if (1 > mday || 31 < mday)
    {  // 本当はもっと厳密にチェックしたほうが良い
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int hour = std::stoi(elements[4].str());
    if (0 > hour || 24 < hour)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int min = std::stoi(elements[5].str());
    if (0 > min || 59 < min)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    float sec = std::stof(elements[6].str());
    if (0 > sec || 60 < sec)
    {  // 閏秒を考慮すると最大値は60
      throw std::invalid_argument("DateTime String Format error");
    }

    if (elements[8].str() == "Z")
    {
      iso8601Time.tm_gmtoff = 0;
    }
    else
    {
      gmtoffset = std::stol(elements[8].str() + elements[10].str()) * 60 * 60 + std::stol(elements[8].str() + elements[11].str()) * 60;
    }

    iso8601Time.tm_year = std::stoi(elements[1].str()) - 1900;
    iso8601Time.tm_mon = mon - 1;
    iso8601Time.tm_mday = mday;
    iso8601Time.tm_hour = hour;
    iso8601Time.tm_min = min;
    iso8601Time.tm_sec = sec - gmtoffset;
    iso8601Time.tm_isdst = 0;  // not use Summer Time
  }
  else if (std::regex_match(time, elements, iso8601Extended))
  {
    unsigned int mon = std::stoi(elements[2].str());
    if (1 > mon || 12 < mon)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int mday = std::stoi(elements[3].str());
    if (1 > mday || 31 < mday)
    {  // 本当はもっと厳密にチェックしたほうが良い
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int hour = std::stoi(elements[4].str());
    if (0 > hour || 24 < hour)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    unsigned int min = std::stoi(elements[5].str());
    if (0 > min || 59 < min)
    {
      throw std::invalid_argument("DateTime String Format error");
    }
    float sec = std::stof(elements[6].str());
    if (0 > sec || 60 < sec)
    {  // 閏秒を考慮すると最大値は60
      throw std::invalid_argument("DateTime String Format error");
    }

    if (elements[8].str() == "Z")
    {
      iso8601Time.tm_gmtoff = 0;
    }
    else
    {
      gmtoffset = std::stol(elements[8].str() + elements[10].str()) * 60 * 60 + std::stol(elements[8].str() + elements[11].str()) * 60;
    }

    iso8601Time.tm_year = std::stoi(elements[1].str()) - 1900;
    iso8601Time.tm_mon = mon - 1;
    iso8601Time.tm_mday = mday;
    iso8601Time.tm_hour = hour;
    iso8601Time.tm_min = min;
    iso8601Time.tm_sec = sec - gmtoffset;
    iso8601Time.tm_isdst = 0;  // not use Summer Time
  }
  else
  {
    throw std::invalid_argument("DateTime String Format error");
  }

  return mktime(&iso8601Time);
}

ISO8601String Chronos::convertLocalToGMT(ISO8601String iso8601local)
{
  std::string formatDateTime("%FT%T");
  std::time_t gmt_t = convertToTime_t(iso8601local);

  // time_tに変換した段階でGMTを表す日時になっているので、tmにする際にはローカルタイムとして扱うことで
  // GMTのtmを作り出す
  tm lt = *std::localtime(&gmt_t);

  std::stringstream ss;
  ss << std::put_time(&lt, formatDateTime.c_str());
  
  return ISO8601String(ss.str() + "Z");
}
