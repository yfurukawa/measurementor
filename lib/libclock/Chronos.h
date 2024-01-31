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

};
