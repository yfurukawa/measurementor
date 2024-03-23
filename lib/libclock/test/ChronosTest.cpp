#include <string>
#include "ChronosTest.h"
#include "../Chronos.h"
#include "../ISO8601String.h"

void ChronosTest::SetUp()
{
  sut = new Chronos();
}

void ChronosTest::TearDown()
{
  delete sut;
}

TEST_F(ChronosTest, convertLocalToGMT_sameDay)
{
  ISO8601String localTime("2024-03-12T12:34:56+09:00");
  ISO8601String expected("2024-03-12T03:34:56Z");
  EXPECT_EQ(expected.get(), sut->convertLocalToGMT(localTime).get());
}

TEST_F(ChronosTest, convertLocalToGMT_yesterday)
{
  ISO8601String localTime("2024-03-12T02:34:56+09:00");
  ISO8601String expected("2024-03-11T17:34:56Z");
  EXPECT_EQ(expected.get(), sut->convertLocalToGMT(localTime).get());
}

TEST_F(ChronosTest, convertLocalToGMT_sameDay_west)
{
  ISO8601String localTime("2024-03-12T12:34:56-10:00");
  ISO8601String expected("2024-03-12T22:34:56Z");
  EXPECT_EQ(expected.get(), sut->convertLocalToGMT(localTime).get());
}

TEST_F(ChronosTest, convertLocalToGMT_tomorrow_west)
{
  ISO8601String localTime("2024-03-12T22:34:56-10:00");
  ISO8601String expected("2024-03-13T08:34:56Z");
  EXPECT_EQ(expected.get(), sut->convertLocalToGMT(localTime).get());
}

TEST_F(ChronosTest, BasicString_GMT)
{
  ISO8601String time("20240219T121212Z");
  EXPECT_EQ(1708312332, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, BasicString_JST)
{
  ISO8601String time("20240219T121212+0900");
  EXPECT_EQ(1708279932, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, BasicString_Other)
{
  ISO8601String time("20240219T121212-0900");
  EXPECT_EQ(1708344732, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, BasicString_microsec)
{
  ISO8601String time("20240219T121212.123456+0900");
  EXPECT_EQ(1708279933, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, ExtendedString_GMT)
{
  ISO8601String time("2024-02-19T12:12:12Z");
  EXPECT_EQ(1708312332, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, ExtendedString_JST)
{
  ISO8601String time("2024-02-19T12:12:12+09:00");
  EXPECT_EQ(1708279932, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, ExtendedString_Other)
{
  ISO8601String time("2024-02-19T12:12:12-09:00");
  EXPECT_EQ(1708344732, sut->convertToTime_t(time));
}

TEST_F(ChronosTest, ExtendedString_microsec)
{
  ISO8601String time("2024-02-19T12:12:12.543211+09:00");
  EXPECT_EQ(1708279933, sut->convertToTime_t(time));
}
