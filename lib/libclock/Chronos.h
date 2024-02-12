/*!
 @file      Chronos.h
 @brief     日時情報を提供する
*/
#pragma once

// ---------------< include >----------------------------
#include "IClock.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     Chronos
 @brief     日時情報を提供する
*/
class Chronos : public IClock
{
    using Clock = std::chrono::system_clock::time_point::clock;
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    Chronos() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    ~Chronos() = default;

    /*!
    @brief      現在日時を得る
    @return     現在日時
    */
    std::time_t now() const override;

    /*!
     @brief     GMT現在時刻をISO8601基本形式で得る
     @return    ISO8601 基本形式で表されたGMT現在時刻文字列
    */
    std::string nowIso8601BasicGmt() const override;

    /*!
     @brief     GMT現在時刻をISO8601拡張形式で得る
     @return    ISO8601 拡張形式で表されたGMT現在時刻文字列
    */
    std::string nowIso8601ExtendedGmt() const override;

    /*!
     @brief     現在時刻をISO8601基本形式で得る
     @return    ISO8601 基本形式で表されたローカル現在時刻文字列
    */
    std::string nowIso8601Basic() const override;

    /*!
     @brief     T現在時刻をISO8601拡張形式で得る
     @return    ISO8601 拡張形式で表されたローカル現在時刻文字列
    */
    std::string nowIso8601Extended() const override;

    /*!
     @brief     ISO8601形式の文字列をtime_tに変換する
     @param[in] iso8601String ISO8601形式の文字列
     @return    入力文字列の日時に相当するtime_t（GMT）
     @attention 戻り値はGMTである
    */
    std::time_t convertToTime_t( std::string iso8601String ) override;
};
