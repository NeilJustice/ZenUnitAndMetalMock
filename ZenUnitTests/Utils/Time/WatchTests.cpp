#include "pch.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<tm>
   {
      static void AssertEqual(const tm& expectedTm, const tm& actualTm)
      {
         ARE_EQUAL(expectedTm.tm_sec, actualTm.tm_sec);
         ARE_EQUAL(expectedTm.tm_min, actualTm.tm_min);
         ARE_EQUAL(expectedTm.tm_hour, actualTm.tm_hour);
         ARE_EQUAL(expectedTm.tm_mday, actualTm.tm_mday);
         ARE_EQUAL(expectedTm.tm_mon, actualTm.tm_mon);
         ARE_EQUAL(expectedTm.tm_year, actualTm.tm_year);
         ARE_EQUAL(expectedTm.tm_wday, actualTm.tm_wday);
         ARE_EQUAL(expectedTm.tm_yday, actualTm.tm_yday);
         ARE_EQUAL(expectedTm.tm_isdst, actualTm.tm_isdst);
      }
   };
}

TESTS(WatchTests)
FACTS(DateTimeNowWithTimeZone_ReturnsLocalTimeNowWithTimeZoneAndTodaysDate)
FACTS(MicrosecondsToThreeDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces)
EVIDENCE

struct WatchSelfMocked : public Zen::Mock<ZenUnit::Watch>
{
   ZENMOCK_NONVOID0_CONST(tm, TMNow)
   ZENMOCK_NONVOID1_CONST(string, TimeZone, const tm&)
};
unique_ptr<WatchSelfMocked> _watchSelfMocked;

STARTUP
{
   _watchSelfMocked = make_unique<WatchSelfMocked>();
}

TEST2X2(DateTimeNowWithTimeZone_ReturnsLocalTimeNowWithTimeZoneAndTodaysDate,
   tm tmNow, const char* expectedDateTimeNowWithTimeZone,
   Tm(0, 1, 0, 0, 0, 0), "1900-01-01 00:00:00 TimeZone",
   Tm(1, 2, 1, 1, 1, 1), "1901-02-02 01:01:01 TimeZone",
   Tm(2, 3, 2, 11, 11, 11), "1902-03-03 11:11:11 TimeZone",
   Tm(11, 31, 99, 23, 59, 59), "1999-12-31 23:59:59 TimeZone",
   Tm(0, 1, 100, 0, 0, 0), "2000-01-01 00:00:00 TimeZone",
   Tm(1, 3, 101, 4, 5, 6), "2001-02-03 04:05:06 TimeZone")
{
   _watchSelfMocked->TMNowMock.Return(tmNow);
   _watchSelfMocked->TimeZoneMock.Return("TimeZone");
   //
   const string dateTimeNowWithTimeZone = _watchSelfMocked->DateTimeNowWithTimeZone();
   //
   ZEN(_watchSelfMocked->TMNowMock.CalledOnce());
   ZEN(_watchSelfMocked->TimeZoneMock.CalledOnceWith(tmNow));
   ARE_EQUAL(expectedDateTimeNowWithTimeZone, dateTimeNowWithTimeZone);
}

static constexpr tm Tm(int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
{
   tm tmNow{};
   tmNow.tm_sec = tmSec;
   tmNow.tm_min = tmMin;
   tmNow.tm_hour = tmHour;
   tmNow.tm_mday = tmMonthDay;
   tmNow.tm_mon = tmMonth;
   tmNow.tm_year = tmYear;
   tmNow.tm_wday = 0;
   tmNow.tm_yday = 0;
   tmNow.tm_isdst = 0;
   return tmNow;
}

TEST2X2(MicrosecondsToThreeDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces,
   unsigned microseconds, const string& expectedReturnValue,
   0, "(0.000ms)",
   1, "(0.001ms)",
   2, "(0.002ms)",
   10, "(0.010ms)",
   12, "(0.012ms)",
   100, "(0.100ms)",
   120, "(0.120ms)",
   123, "(0.123ms)",
   1000, "(1.000ms)",
   1234, "(1.234ms)",
   12345, "(12.345ms)",
   123456, "(123.456ms)",
   1234567, "(1234.567ms)",
   12345678, "(12345.678ms)",
   123456789, "(123456.789ms)",
   1234567890, "(1234567.890ms)")
{
   const string threeDecimalPlaceMilliseconds =
      Watch::MicrosecondsToThreeDecimalPlaceMillisecondsString(microseconds);
   ARE_EQUAL(expectedReturnValue, threeDecimalPlaceMilliseconds);
}

RUN_TESTS(WatchTests)
