/*!
 @file      ISO8601StringTest.h
 @brief     ISO8601Stringをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
class ISO8601String;

/*!
 @file      ISO8601StringTest.h
 @brief     ISO8601Stringをテストする
*/
class ISO8601StringTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    ISO8601StringTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~ISO8601StringTest() = default;

protected:
    ISO8601String* sut;

    void SetUp();
    void TearDown();
};
