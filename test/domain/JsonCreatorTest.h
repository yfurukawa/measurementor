/*!
 @file      JsonCreatorTest.h
 @brief     JsonCreatorをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class JsonCreator;

/*!
 @file      JsonCreatorTest.h
 @brief     JsonCreatorをテストする
*/
class JsonCreatorTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    JsonCreatorTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~JsonCreatorTest() = default;

protected:
    JsonCreator* sut;

    void SetUp();
    void TearDown();
};

}
