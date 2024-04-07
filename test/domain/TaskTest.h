/*!
 @file      TaskTest.h
 @brief     Taskをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Task;

/*!
 @file      TaskTest.h
 @brief     Taskをテストする
*/
class TaskTest : public ::testing::Test
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  TaskTest() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~TaskTest() = default;

protected:
  Task* sut;

  void SetUp();
  void TearDown();
};

}  // namespace measurementor
