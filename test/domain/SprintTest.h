/*!
 @file      SprintTest.h
 @brief     Sprintをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Sprint;

/*!
 @file      SprintTest.h
 @brief     Sprintをテストする
*/
class SprintTest : public ::testing::Test
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  SprintTest() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~SprintTest() = default;

protected:
  Sprint* sut;

  void SetUp();
  void TearDown();
};

}  // namespace measurementor
