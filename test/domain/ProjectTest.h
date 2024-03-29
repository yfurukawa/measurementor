/*!
 @file      ProjectTest.h
 @brief     Projectをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class Project;

/*!
 @file      ProjectTest.h
 @brief     Projectをテストする
*/
class ProjectTest : public ::testing::Test
{
public:
  /*!
   @brief  デフォルトコンストラクタ
  */
  ProjectTest() = default;

  /*!
   @brief  デフォルトデストラクタ
  */
  virtual ~ProjectTest() = default;

protected:
  Project* sut;

  void SetUp();
  void TearDown();
};

}  // namespace measurementor
