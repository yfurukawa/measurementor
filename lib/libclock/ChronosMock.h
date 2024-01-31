/*!
 @file      ChronosMock.h
 @brief     テスト用に特定の日時情報を提供する
*/
#pragma once

// ---------------< include >----------------------------
#include "IClock.h"

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

};
