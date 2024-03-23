/*!
 @file      ChronosTest.h
 @brief     Chronosをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
class Chronos;

/*!
 @file      ChronosTest.h
 @brief     Chronosをテストする
*/
class ChronosTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    ChronosTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~ChronosTest() = default;

protected:
    Chronos* sut;

    void SetUp();
    void TearDown();
};
