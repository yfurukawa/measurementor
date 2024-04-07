/*!
 @file      MetricCalculatorTest.h
 @brief     MetricCalculatorをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class MetricCalculatorSpy;

/*!
 @file      MetricCalculatorTest.h
 @brief     MetricCalculatorをテストする
*/
class MetricCalculatorTest : public ::testing::Test
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  MetricCalculatorTest() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~MetricCalculatorTest() = default;

protected:
  MetricCalculatorSpy* sut;

  void SetUp();
  void TearDown();
};

}  // namespace measurementor
