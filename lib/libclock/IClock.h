/*!
 @file      IClock.h
 @brief     日時情報を提供するクラス共通のインターフェース
*/
#pragma once

// ---------------< include >----------------------------
#include <chrono>
#include "ToISO8601String.hpp"

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

};
