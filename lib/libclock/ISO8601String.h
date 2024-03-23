/*!
 @file      ISO8601String.hpp
 @brief     ISO8601フォーマット準拠のドメインプリミティブ
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     ISO8601String
 @brief     ISO8601形式の日時を表す文字列を保持する
*/
class ISO8601String
{
private:
    ISO8601String() = delete;

public:
    explicit ISO8601String(std::string iso8601String);

    /*!
     @brief     与えられた文字列がISO8601のフォーマットに準拠しているか確認する
     @param[in] iso8601string  変換元となるISO8601形式の文字列
     @return    true : 準拠している
     @attention 許容しているフォーマットは、"YYYYMMDDThhmmss"（基本形式）又は"YYYY-MM-DDThh:mm:ss"（拡張形式）に
                それぞれの形式に従ったタイムゾーンを加えた形式である。
    */
    bool checkFormat( std::string iso8601string );

    /*!
     @brief     保持している日時を返す
     @return    ISO8601形式の日時
    */
    std::string get();
    
protected:
    std::string iso8601String_;  //!< フォーマットチェック済みのISO8601形式の日時
};
