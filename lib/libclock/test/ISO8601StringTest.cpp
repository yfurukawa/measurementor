#include <exception>
#include "ISO8601StringTest.h"
#include "../ISO8601String.h"
#include "gtest/gtest.h"

void ISO8601StringTest::SetUp()
{
  sut = nullptr;
}

void ISO8601StringTest::TearDown()
{
  if (sut != nullptr)
  {
    delete sut;
  }
}

TEST_F(ISO8601StringTest, checkFormat_ShortLength)
{
  EXPECT_THROW(new ISO8601String("20240219T121212"), std::invalid_argument);
}

TEST_F(ISO8601StringTest, checkFormat_LongLength)
{
  EXPECT_THROW(new ISO8601String("2024-02-19T12:12:12.1234567+09:00"), std::invalid_argument);
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeDelimiterInCorrect_Basic)
{
  EXPECT_THROW(new ISO8601String("2024219T121212.1234567+0900"), std::invalid_argument);
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeDelimiterInCorrect_Extended)
{
  EXPECT_THROW(new ISO8601String("2024-2-19T12:12:12+09:00"), std::invalid_argument);
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_GMT)
{
  std::string expected("20240219T121212.123456Z");
  sut = new ISO8601String(expected);
  EXPECT_EQ(expected, sut->get());
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_JST)
{
  std::string expected("20240219T121212.123456+0900");
  sut = new ISO8601String(expected);
  EXPECT_EQ(expected, sut->get());
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect2_Basic_JST)
{
  std::string expected("20240219T121212+0900");
  sut = new ISO8601String(expected);
  EXPECT_EQ(expected, sut->get());
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_ET)
{
  std::string expected("20240219T121212.123456-0900");
  sut = new ISO8601String(expected);
  EXPECT_EQ(expected, sut->get());
}

TEST_F(ISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Extended_GMT)
{
  std::string expected("2024-02-19T12:12:12.123456Z");
  sut = new ISO8601String(expected);
  EXPECT_EQ(expected, sut->get());
}
