/*!
 @file      IndexTest.h
 @brief     Indexをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------
class Index;

/*!
 @file      IndexTest.h
 @brief     Indexをテストする
*/
class IndexTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    IndexTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~IndexTest() = default;

protected:
    Index* sut;

    void SetUp();
    void TearDown();
};

}
