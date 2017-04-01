#include "pch.h"
#include "ZenUnit/Utils/Time/Watch.h"

template<>
struct ZenUnitEqualizer<tm>
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

namespace ZenUnit
{
   TESTS(WatchTests)
   SPECX(TimeZoneDateTimeNow_ReturnsLocalTimeNowWithTimeZoneAndTodaysDate)
   SPECEND

   struct WatchSelfMocked : public Zen::Mock<ZenUnit::Watch>
   {
      ZENMOCK_NONVOID0_CONST(tm, TMNow)
      ZENMOCK_NONVOID1_CONST(string, TimeZone, const tm&)
   };
   unique_ptr<WatchSelfMocked> _watchSelfMocked;

   STARTUP
   {
      _watchSelfMocked = std::make_unique<WatchSelfMocked>();
   }

   TEST2X2(TimeZoneDateTimeNow_ReturnsLocalTimeNowWithTimeZoneAndTodaysDate,
      tm tmNow, string expectedReturnValue,
      Tm(0, 0, 1, 0, 00, 00, 00), "00:00:00 TimeZone on Sunday January 1, 1900",
      Tm(1, 1, 2, 1, 01, 01, 01), "01:01:01 TimeZone on Monday February 2, 1901",
      Tm(2, 2, 3, 2, 11, 11, 11), "11:11:11 TimeZone on Tuesday March 3, 1902",
      Tm(3, 3, 30, 99, 12, 00, 00), "12:00:00 TimeZone on Wednesday April 30, 1999",
      Tm(4, 4, 1, 100, 12, 45, 01), "12:45:01 TimeZone on Thursday May 1, 2000",
      Tm(5, 5, 1, 101, 13, 01, 01), "13:01:01 TimeZone on Friday June 1, 2001",
      Tm(6, 6, 1, 109, 00, 00, 00), "00:00:00 TimeZone on Saturday July 1, 2009",
      Tm(0, 7, 1, 110, 00, 00, 00), "00:00:00 TimeZone on Sunday August 1, 2010",
      Tm(1, 8, 1, 111, 00, 00, 00), "00:00:00 TimeZone on Monday September 1, 2011",
      Tm(2, 9, 1, 116, 00, 00, 00), "00:00:00 TimeZone on Tuesday October 1, 2016",
      Tm(3, 10, 1, 117, 11, 30, 45), "11:30:45 TimeZone on Wednesday November 1, 2017",
      Tm(4, 11, 31, 118, 23, 59, 59), "23:59:59 TimeZone on Thursday December 31, 2018")
   {
      _watchSelfMocked->TMNowMock.ExpectAndReturn(tmNow);
      _watchSelfMocked->TimeZoneMock.ExpectAndReturn("TimeZone");
      //
      const string timeZoneDateTimeNow = _watchSelfMocked->TimeZoneDateTimeNow();
      //
      ZEN(_watchSelfMocked->TMNowMock.AssertCalledOnce());
      ZEN(_watchSelfMocked->TimeZoneMock.AssertCalledOnceWith(tmNow));
      ARE_EQUAL(expectedReturnValue, timeZoneDateTimeNow);
   }

   static tm Tm(int tmWeekDay, int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
   {
      tm tmNow{};
      tmNow.tm_sec = tmSec;
      tmNow.tm_min = tmMin;
      tmNow.tm_hour = tmHour;
      tmNow.tm_mday = tmMonthDay;
      tmNow.tm_mon = tmMonth;
      tmNow.tm_year = tmYear;
      tmNow.tm_wday = tmWeekDay;
      tmNow.tm_yday = 0;
      tmNow.tm_isdst = 0;
      return tmNow;
   }

   }; RUN(WatchTests)
}
