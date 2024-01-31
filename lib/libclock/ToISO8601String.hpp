/*!
 @file      ToISO8601String.hpp
 @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す
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
namespace AbstLogger {

// ---------< forward declaration >----------------------
using defaultClock = std::chrono::system_clock;
constexpr auto formatDateTime = "%FT%T";
constexpr auto formatTimeZone = "%z";

/*!
 @fn        getSubSecondString
 @brief     必要な精度の「秒」になるように小数点以下の文字列を返す
 @tparam    TimePoint TimePointの型
 @tparam    SecondUnit 秒の精度（小数点以下）
 @param[in] timePoint 時刻情報
 @return    秒の小数点以下を表す文字列
*/
template< typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds >
auto getSubSecondString( const TimePoint& timePoint ) -> std::string
{
    constexpr auto ratioInReal = static_cast< long double >( SecondUnit::period::num ) / SecondUnit::period::den;
    constexpr auto subSecondDegits = -std::log10( ratioInReal );

    if( subSecondDegits < 1 ) {
        return "";
    }

    const auto full = std::chrono::duration_cast< std::chrono::duration< long double >>(timePoint.time_since_epoch());
    const auto sec = std::chrono::duration_cast< std::chrono::seconds >( timePoint.time_since_epoch() );
    const auto subSecondInReal = ( full - sec ).count();

    std::stringstream s;
    s << std::fixed << std::setprecision( subSecondDegits ) << subSecondInReal;
    constexpr auto inDot = 1;
    return s.str().substr( inDot );
}

/*!
 @fn        toString_iso8601_gmt
 @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す（GMT）
 @tparam    TimePoint TimePointの型
 @tparam    SecondUnit 秒の精度（小数点以下）
 @param[in] timePoint 時刻情報
 @return    ISO8601準拠の日付文字列（GMT）
*/
template< typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds >
auto toString_iso8601_gmt( const TimePoint& timePoint = TimePoint::clock::now() ) -> std::string
{
    const auto& ct = TimePoint::clock::to_time_t( timePoint );
    auto gt = std::gmtime( &ct );
    std::stringstream ss;
    ss  << std::put_time( gt, formatDateTime )
        << getSubSecondString< TimePoint, SecondUnit >( timePoint )
        << "Z";

    return ss.str();
}

/*!
 @fn        toString_iso8601
 @brief     ISO8601で規定された日時フォーマットに準拠した文字列を返す（ローカルタイムゾーン）
 @tparam    TimePoint TimePointの型
 @tparam    SecondUnit 秒の精度（小数点以下）
 @param[in] timePoint 時刻情報
 @return    ISO8601準拠の日付文字列（ローカルタイムゾーン）
*/
template< typename TimePoint = defaultClock::time_point, typename SecondUnit = std::chrono::seconds >
auto toString_iso8601( const TimePoint& timePoint = TimePoint::clock::now() ) -> std::string
{
    const auto& ct = TimePoint::clock::to_time_t( timePoint );
    auto lt = *std::localtime( &ct );

    // ISO8601のTimeZoneの規定はコロン入りなのでそのフォーマットに合わせる
    std::stringstream tzss;
    tzss << std::put_time( &lt, formatTimeZone );
    std::string tz( tzss.str() );
    tz.insert( tz.length() - 2, ":" );

    std::stringstream ss;
    ss  << std::put_time( &lt, formatDateTime )
        << getSubSecondString< TimePoint, SecondUnit >( timePoint )
        << tz;

    return ss.str();
}

}
