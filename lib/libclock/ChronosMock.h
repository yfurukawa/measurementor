/*!
 @file      ChronosMock.h
 @brief     テスト用に特定の日時情報を提供する
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <ctime>
#include <string>
#include "IClock.h"
#include "ISO8601String.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     ChronosMock
 @brief     テスト用に特定の日時情報を提供する
*/
class ChronosMock : public IClock
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  ChronosMock() = default;

  /*!
  @brief  デフォルトデストラクタ
  */
  ~ChronosMock() = default;

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
  std::time_t convertToTime_t(ISO8601String iso8601String) override;

private:
  ISO8601String returnDateTimeGMT_;  //!< テスト時に戻り値として欲しいGMT日時
  ISO8601String returnDateTimeLT_;   //!< テスト時に戻り値として欲しいLocal日時
  std::time_t returnTime_t_;         //!< テスト時に戻り値として欲しい日時のtime_t
};
