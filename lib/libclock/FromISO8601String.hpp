/*!
 @file      FromISO8601String.hpp
 @brief     ISO8601で規定された日時フォーマットの文字列をtime_tに変換する
 @attention 返されるtime_tはGMTとなる。
*/
#pragma once

// ---------------< include >----------------------------
#include <chrono>
#include <exception>
#include <regex>
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
std::regex iso8601Basic("([0-9]{4})([01][0-9])([0-3][0-9])T([0-2][0-9])([0-5][0-9])([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2})([0-9]{2}))?");
std::regex iso8601Extended("([0-9]{4})-([01][0-9])-([0-3][0-9])T([0-2][0-9]):([0-5][0-9]):([0-5][0-9](.[0-9]{1,6})?)([Z+-])(([0-9]{2}):([0-9]{2}))?");

/*!
 @fn        checkFormat
 @brief     与えられた文字列がISO8601のフォーマットに準拠しているか確認する
 @param[in] iso8601string  変換元となるISO8601形式の文字列
 @return    true : 準拠している
 @attention 許容しているフォーマットは、"YYYYMMDDThhmmss"（基本形式）又は"YYYY-MM-DDThh:mm:ss"（拡張形式）に
            それぞれの形式に従ったタイムゾーンを加えた形式である。
*/
bool checkFormat( std::string iso8601string )
{

    // （UTC基本形式）、（UTC拡張形式／LocalTZ基本形式）又は（LocalTZ拡張形式）のいづれかに合致しない場合は、詳細に確認する必要はない
    if( iso8601string.length() < 16 || iso8601string.length() > 32 ) {
        return false;
    }

    // 日付と時刻が’T'で区切られていなければならない
    if( !(iso8601string.find_first_of('T') == 8 || iso8601string.find_first_of('T') == 10) ) {
        return false;
    }

    // 基本的なフォーマットが合致しているか確認する
    // 値の範囲外の確認はしていない
    if( std::regex_match( iso8601string, iso8601Basic ) || std::regex_match( iso8601string, iso8601Extended ) ) {
        return true;
    }

    return false;
}

/*!
 @fn        ToTimeT
 @brief     ISO8601形式の文字列をtime_tに変換する
 @param[in] iso8601String ISO8601形式の文字列
 @return    入力文字列の日時に相当するtime_t（GMT）
 @attention 戻り値はGMTである
*/
std::time_t ToTimeT( std::string iso8601string )
{
    if( !checkFormat( iso8601string ) )
    {
        throw std::invalid_argument("DateTime String Format error");
    }

    struct tm iso8601Time;
    std::smatch elements;
    long gmtoffset(0);

    if( std::regex_match( iso8601string, elements, iso8601Basic) )
    {
        unsigned int mon = std::stoi(elements[2].str());
        if( 1 > mon || 12 < mon ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int mday = std::stoi(elements[3].str());
        if( 1 > mday || 31 < mday ) {    // 本当はもっと厳密にチェックしたほうが良い
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int hour = std::stoi(elements[4].str());
        if( 0 > hour || 24 < hour ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int min = std::stoi(elements[5].str());
        if( 0 > min || 59 < min ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        float sec = std::stof(elements[6].str());
        if( 0 > sec || 60 < sec ) {   // 閏秒を考慮すると最大値は60
            throw std::invalid_argument("DateTime String Format error");
        }

        if( elements[8].str() == "Z" )
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
        iso8601Time.tm_isdst = 0;   // not use Summer Time
    }
    else if( std::regex_match( iso8601string, elements, iso8601Extended) )
    {
        unsigned int mon = std::stoi(elements[2].str());
        if( 1 > mon || 12 < mon ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int mday = std::stoi(elements[3].str());
        if( 1 > mday || 31 < mday ) {    // 本当はもっと厳密にチェックしたほうが良い
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int hour = std::stoi(elements[4].str());
        if( 0 > hour || 24 < hour ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        unsigned int min = std::stoi(elements[5].str());
        if( 0 > min || 59 < min ) {
            throw std::invalid_argument("DateTime String Format error");
        }
        float sec = std::stof(elements[6].str());
        if( 0 > sec || 60 < sec ) {   // 閏秒を考慮すると最大値は60
            throw std::invalid_argument("DateTime String Format error");
        }

        if( elements[8].str() == "Z" )
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
        iso8601Time.tm_isdst = 0;   // not use Summer Time
    }
    else
    {
        throw std::invalid_argument("DateTime String Format error");
    }

    return mktime(&iso8601Time);
}