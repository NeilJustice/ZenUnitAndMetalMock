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

static tm Tm(int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
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

RUN_TESTS(WatchTests)


namespace ZenUnit
{
   TESTS(StopwatchTests)
   AFACT(Constructor_SetsNowFunction)
   AFACT(Start_SetsStartTimeToNow)
   AFACT(Stop_StartNotPreviouslyCalled_Returns0)
   AFACT(Stop_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   EVIDENCE

   Stopwatch _stopwatch;
   ZENMOCK_NONVOID0_STATIC(
      chrono::time_point<chrono::high_resolution_clock>,
      chrono::high_resolution_clock, now)

      STARTUP
   {
      _stopwatch.call_highres_now = ZENMOCK_BIND0(now_ZenMock);
   }

   TEST(Constructor_SetsNowFunction)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch.call_highres_now);
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock>
         nonDefaultTimePoint = chrono::high_resolution_clock::now();
      now_ZenMock.Return(nonDefaultTimePoint);
      //
      _stopwatch.Start();
      //
      now_ZenMock.CalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
   }

   TEST(Stop_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.Stop());
      ARE_EQUAL(0, _stopwatch.Stop());
   }

   TEST(Stop_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      startTime += chrono::milliseconds(Random<unsigned>());
      const unsigned short randomMicrosecondDuration = Random<unsigned short>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::microseconds(randomMicrosecondDuration);
      now_ZenMock.Return(stopTime);
      _stopwatch._startTime = startTime;
      //
      const unsigned elapsedMicroseconds = _stopwatch.Stop();
      //
      ZEN(now_ZenMock.CalledOnce());
      ARE_EQUAL(randomMicrosecondDuration, elapsedMicroseconds);
   }

   RUN_TESTS(StopwatchTests)
}
