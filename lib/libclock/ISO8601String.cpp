/*!
 @file      ISO8601String.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "ISO8601String.h"
#include <chrono>
#include <exception>
#include <regex>

ISO8601String::ISO8601String(std::string iso8601String)
{
  if (!checkFormat(iso8601String))
  {
    throw std::invalid_argument("DateTime String Format error : " + iso8601String);
  }
  iso8601String_ = iso8601String;
}

bool ISO8601String::checkFormat(std::string iso8601string)
{
  std::regex iso8601Basic(
    "([0-9]{4})([01][0-9])([0-3][0-9])T([0-2][0-9])([0-5][0-9])([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2})([0-9]{2}))?");
  std::regex iso8601Extended(
    "([0-9]{4})-([01][0-9])-([0-3][0-9])T([0-2][0-9]):([0-5][0-9]):([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2}):([0-9]{2}))?");

  // （UTC基本形式）、（UTC拡張形式／LocalTZ基本形式）又は（LocalTZ拡張形式）のいづれかに合致しない場合は、詳細に確認する必要はない
  if (iso8601string.length() < 16 || iso8601string.length() > 32)
  {
    return false;
  }

  // 日付と時刻が’T'で区切られていなければならない
  if (!(iso8601string.find_first_of('T') == 8 || iso8601string.find_first_of('T') == 10))
  {
    return false;
  }

  // 基本的なフォーマットが合致しているか確認する
  // 値の範囲外の確認はしていない
  if (std::regex_match(iso8601string, iso8601Basic) || std::regex_match(iso8601string, iso8601Extended))
  {
    return true;
  }

  return false;
}

std::string ISO8601String::get() const
{
  return iso8601String_;
}
