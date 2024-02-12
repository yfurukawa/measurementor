#include <exception>
#include "../FromISO8601String.hpp"
#include "gtest/gtest.h"

TEST(FromISO8601StringTest, checkFormat_ShortLength)
{
    EXPECT_FALSE( checkFormat("20240219T121212") );
}

TEST(FromISO8601StringTest, checkFormat_LongLength)
{
    EXPECT_FALSE( checkFormat("2024-02-19T12:12:12.1234567+09:00") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeDelimiterInCorrect_Basic)
{
    EXPECT_FALSE( checkFormat("2024219T121212.1234567+0900") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeDelimiterInCorrect_Extended)
{
    EXPECT_FALSE( checkFormat("2024-2-19T12:12:12+09:00") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_GMT)
{
    EXPECT_TRUE( checkFormat("20240219T121212.123456Z") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_JST)
{
    EXPECT_TRUE( checkFormat("20240219T121212.123456+0900") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect2_Basic_JST)
{
    EXPECT_TRUE( checkFormat("20240219T121212+0900") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Basic_ET)
{
    EXPECT_TRUE( checkFormat("20240219T121212.123456-0900") );
}

TEST(FromISO8601StringTest, checkFormat_DateAndTimeFormatInCorrect_Extended_GMT)
{
    EXPECT_TRUE( checkFormat("2024-02-19T12:12:12.123456Z") );
}


TEST(FromISO8601StringTest, BasicString_GMT)
{
    EXPECT_EQ(1708312332, ToTimeT("20240219T121212Z") );
}

TEST(FromISO8601StringTest, BasicString_JST)
{
    EXPECT_EQ(1708279932, ToTimeT("20240219T121212+0900") );
}

TEST(FromISO8601StringTest, BasicString_Other)
{
    EXPECT_EQ(1708344732, ToTimeT("20240219T121212-0900") );
}

TEST(FromISO8601StringTest, BasicString_microsec)
{
    EXPECT_EQ(1708279933, ToTimeT("20240219T121212.123456+0900") );
}

TEST(FromISO8601StringTest, ExtendedString_GMT)
{
    EXPECT_EQ(1708312332, ToTimeT("2024-02-19T12:12:12Z") );
}

TEST(FromISO8601StringTest, ExtendedString_JST)
{
    EXPECT_EQ(1708279932, ToTimeT("2024-02-19T12:12:12+09:00") );
}

TEST(FromISO8601StringTest, ExtendedString_Other)
{
    EXPECT_EQ(1708344732, ToTimeT("2024-02-19T12:12:12-09:00") );
}

TEST(FromISO8601StringTest, ExtendedString_microsec)
{
    EXPECT_EQ(1708279933, ToTimeT("2024-02-19T12:12:12.543211+09:00") );
}
