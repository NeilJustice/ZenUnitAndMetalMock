#include "pch.h"

namespace ZenUnit
{
   template<>
   class Equalizer<tm>
   {
   public:
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

   TESTS(WatchTests)
   FACTS(DateTimeNow_ReturnsLocalDateTimeNow)
   AFACT(TimeZone_ReturnTimeZoneOfExecutingProcess)
   FACTS(MillisecondsToBracketedMillisecondsString_DoesSo)
   EVIDENCE

   class WatchSelfMocked : public Metal::Mock<ZenUnit::Watch>
   {
   public:
      METALMOCK_NONVOID0_CONST(tm, TMNow)
      METALMOCK_NONVOID1_CONST(string, TimeZone, const tm&)
   };
   unique_ptr<WatchSelfMocked> _watchSelfMocked;

   STARTUP
   {
      _watchSelfMocked = make_unique<WatchSelfMocked>();
   }

   TEST2X2(DateTimeNow_ReturnsLocalDateTimeNow,
      const tm& tmNow, const string& expectedDateTimeNowPrefix,
      Tm(0, 1, 0, 0, 0, 0), "1900-01-01 12:00:00 AM ",
      Tm(1, 2, 1, 1, 1, 1), "1901-02-02 01:01:01 AM ",
      Tm(2, 3, 2, 11, 11, 11), "1902-03-03 11:11:11 AM ",
      Tm(11, 31, 99, 23, 59, 59), "1999-12-31 11:59:59 PM ",
      Tm(0, 1, 100, 0, 0, 0), "2000-01-01 12:00:00 AM ",
      Tm(1, 3, 101, 4, 5, 6), "2001-02-03 04:05:06 AM ")
   {
      _watchSelfMocked->TMNowMock.Return(tmNow);
      const string timeZone = _watchSelfMocked->TimeZoneMock.ReturnRandom();
      //
      const string dateTimeNow = _watchSelfMocked->DateTimeNow();
      //
      METALMOCK(_watchSelfMocked->TMNowMock.CalledOnce());
      METALMOCK(_watchSelfMocked->TimeZoneMock.CalledOnceWith(tmNow));
      const string expectedDateTimeNow = expectedDateTimeNowPrefix + timeZone;
      ARE_EQUAL(expectedDateTimeNow, dateTimeNow);
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

   TEST(TimeZone_ReturnTimeZoneOfExecutingProcess)
   {
      Watch watch;
      const tm tmNow = watch.TMNow();
      //
      const string timeZone = watch.TimeZone(tmNow);
      //
      array<char, 64> expectedTimeZoneChars{};
      strftime(expectedTimeZoneChars.data(), sizeof(expectedTimeZoneChars), "%Z", &tmNow);
      const string expectedTimeZone(expectedTimeZoneChars.data());
      ARE_EQUAL(expectedTimeZone, timeZone);
   }

   TEST2X2(MillisecondsToBracketedMillisecondsString_DoesSo,
      unsigned short milliseconds, const string& expectedReturnValue,
      static_cast<unsigned short>(0), "[0ms]",
      static_cast<unsigned short>(1), "[1ms]",
      static_cast<unsigned short>(2), "[2ms]",
      numeric_limits<unsigned short>::max(), "[65535ms]")
   {
      const string bracketedMillisecondsString = Watch::MillisecondsToBracketedMillisecondsString(milliseconds);
      ARE_EQUAL(expectedReturnValue, bracketedMillisecondsString);
   }

   RUN_TESTS(WatchTests)
}
