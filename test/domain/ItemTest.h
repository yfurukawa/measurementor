/*!
 @file      ItemTest.h
 @brief     Itemをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Item;

/*!
 @file      ItemTest.h
 @brief     Itemをテストする
*/
class ItemTest : public ::testing::Test
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  ItemTest() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~ItemTest() = default;

protected:
  Item* sut;

  void SetUp();
  void TearDown();
};

}  // namespace measurementor
