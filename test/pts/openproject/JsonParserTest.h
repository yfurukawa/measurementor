/*!
 @file      JsonParserTest.h
 @brief     JsonParserをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------
class JsonParser;

/*!
 @file      JsonParserTest.h
 @brief     JsonParserをテストする
*/
class JsonParserTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    JsonParserTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~JsonParserTest() = default;

protected:
    JsonParser* sut;

    void SetUp();
    void TearDown();
};

}
