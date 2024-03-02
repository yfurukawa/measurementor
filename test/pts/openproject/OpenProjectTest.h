/*!
 @file      OpenProjectTest.h
 @brief     OpenProjectをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
class TcpClient;

namespace pts
{

// ---------< forward declaration >----------------------
class OpenProject;

/*!
 @file      OpenProjectTest.h
 @brief     OpenProjectをテストする
*/
class OpenProjectTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    OpenProjectTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~OpenProjectTest() = default;

protected:
    OpenProject* sut;

    void SetUp();
    void TearDown();
};

}
