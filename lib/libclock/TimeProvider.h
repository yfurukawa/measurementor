/*!
 @file      TimeProvider.h
 @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す
 @attention 本コードは@usagiさんのQiita記事（https://qiita.com/usagi/items/ab8ec7014d1b1b1894d2）からの引用である
 @copyright Copyright 2016 Usagi Ito
*/
#pragma once

// ---------------< include >----------------------------
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     TimeProvider
 @brief     日時情報を提供する
*/
class TimeProvider final
{
public:
  using defaultClock = std::chrono::system_clock;

  /*!
   @brief  デフォルトコンストラクタ
  */
  TimeProvider();

  /*!
   @brief  デフォルトデストラクタ
  */
  ~TimeProvider() = default;

  /*!
   @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す（GMT）
   @tparam    TimePoint TimePointの型
   @tparam    SecondUnit 秒の精度（小数点以下）
   @param[in] timePoint 時刻情報
   @return    ISO8601準拠の日付文字列（GMT）
  */
  template <typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds>
  std::string toString_iso8601_gmt(const TimePoint& timePoint = TimePoint::clock::now())
  {
    const auto& ct = TimePoint::clock::to_time_t(timePoint);
    auto gt = std::gmtime(&ct);
    std::stringstream ss;
    ss << std::put_time(gt, formatDateTime_.c_str()) << getSubSecondString<TimePoint, SecondUnit>(timePoint) << "Z";

    return ss.str();
  };

  /*!
   @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す（ローカルタイムゾーン）
   @tparam    TimePoint TimePointの型
   @tparam    SecondUnit 秒の精度（小数点以下）
   @param[in] timePoint 時刻情報
   @return    ISO8601準拠の日付文字列（ローカルタイムゾーン）
  */
  template <typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds>
  std::string toString_iso8601(const TimePoint& timePoint = TimePoint::clock::now())
  {
    const auto& ct = TimePoint::clock::to_time_t(timePoint);
    auto lt = *std::localtime(&ct);

    // ISO8601のTimeZoneの規定はコロン入りなのでそのフォーマットに合わせる
    std::stringstream tzss;
    tzss << std::put_time(&lt, formatTimeZone_.c_str());
    std::string tz(tzss.str());
    tz.insert(tz.length() - 2, ":");

    std::stringstream ss;
    ss << std::put_time(&lt, formatDateTime_.c_str()) << getSubSecondString<TimePoint, SecondUnit>(timePoint) << tz;

    return ss.str();
  };

private:
  std::string formatDateTime_;  //!< 日付のフォーマット（YYYY-MM-DDTHH:mm:DD）
  std::string formatTimeZone_;  //!< タイムゾーンのフォーマット

  /*!
   @brief     必要な精度の「秒」になるように小数点以下の文字列を返す
   @tparam    TimePoint TimePointの型
   @tparam    SecondUnit 秒の精度（小数点以下）
   @param[in] timePoint 時刻情報
   @return    秒の小数点以下を表す文字列
  */
  template <typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds>
  std::string getSubSecondString(const TimePoint& timePoint)
  {
    constexpr auto ratioInReal = static_cast<long double>(SecondUnit::period::num) / SecondUnit::period::den;
    constexpr auto subSecondDegits = -std::log10(ratioInReal);

    if (subSecondDegits < 1)
    {
      return "";
    }

    const auto full = std::chrono::duration_cast<std::chrono::duration<long double>>(timePoint.time_since_epoch());
    const auto sec = std::chrono::duration_cast<std::chrono::seconds>(timePoint.time_since_epoch());
    const auto subSecondInReal = (full - sec).count();

    std::stringstream s;
    s << std::fixed << std::setprecision(subSecondDegits) << subSecondInReal;
    constexpr auto inDot = 1;
    return s.str().substr(inDot);
  }
};
