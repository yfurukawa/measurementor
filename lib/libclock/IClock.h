/*!
 @file      IClock.h
 @brief     日時情報を提供するクラス共通のインターフェース
*/
#pragma once

// ---------------< include >----------------------------
#include <chrono>
#include <string>
#include "ISO8601String.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     IClock
 @brief     日時情報を提供するクラス共通のインターフェース
*/
class IClock
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    IClock() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~IClock() = default;

    /*!
    @brief      現在日時を得る
    @return     現在日時
    */
    virtual std::time_t now() const = 0;

    /*!
     @brief     GMT現在時刻をISO8601基本形式で得る
     @return    ISO8601 基本形式で表されたGMT現在時刻文字列
    */
    virtual std::string nowIso8601BasicGmt() const = 0;

    /*!
     @brief     GMT現在時刻をISO8601拡張形式で得る
     @return    ISO8601 拡張形式で表されたGMT現在時刻文字列
    */
    virtual std::string nowIso8601ExtendedGmt() const = 0;

    /*!
     @brief     現在時刻をISO8601基本形式で得る
     @return    ISO8601 基本形式で表されたローカル現在時刻文字列
    */
    virtual std::string nowIso8601Basic() const = 0;

    /*!
     @brief     T現在時刻をISO8601拡張形式で得る
     @return    ISO8601 拡張形式で表されたローカル現在時刻文字列
    */
    virtual std::string nowIso8601Extended() const = 0;

    /*!
     @brief     ISO8601形式の文字列をtime_tに変換する
     @param[in] iso8601String ISO8601形式の文字列
     @return    入力文字列の日時に相当するtime_t（GMT）
     @attention 戻り値はGMTである
    */
    virtual std::time_t convertToTime_t(ISO8601String iso8601String ) = 0;

    /*!
     @brief     ISO8601形式のローカルタイムをISO8601形式のGMTに変換する
     @param[in] iso8601local ISO8601形式のローカルタイム
     @return    ISO8601形式のGMT
    */
    virtual std::string convertLocalToGMT(std::string iso8601local) = 0;
};
