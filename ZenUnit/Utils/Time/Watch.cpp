#include "pch.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Time/Watch.h"

namespace ZenUnit
{
   // Returns now in format "Monday January 1, 2016 at 00:00:00 <Timezone>"
   string Watch::TimeZoneDateTimeNow() const
   {
      const tm tmNow = TMNow();
      ostringstream builder;
      const char* const weekDayString = TMWeekDayToWeekDayString(tmNow.tm_wday);
      const char* const monthString = TMMonthToMonthString(tmNow.tm_mon);
      const string timeZone = TimeZone(tmNow);
      builder << setw(2) << setfill('0') << tmNow.tm_hour << ':'
              << setw(2) << setfill('0') << tmNow.tm_min << ':'
              << setw(2) << setfill('0') << tmNow.tm_sec << ' '
              << timeZone << " on " << weekDayString << ' ' << monthString << ' ' << tmNow.tm_mday << ", " << (tmNow.tm_year + 1900);
      const string weekdayDateTimeZoneNow = builder.str();
      return weekdayDateTimeZoneNow;
   }

   tm Watch::TMNow() const
   {
      const chrono::time_point<chrono::system_clock> nowTimePoint = chrono::system_clock::now();
#ifdef __linux__
      tm* tmNow = nullptr;
      long nowTimeT = chrono::system_clock::to_time_t(nowTimePoint);
      tmNow = localtime(&nowTimeT);
      return *tmNow;
#elif _WIN32
      const __time64_t nowTimeT = chrono::system_clock::to_time_t(nowTimePoint);
      tm tmNow;
      const errno_t localtimeResult = localtime_s(&tmNow, &nowTimeT);
      assert_true(localtimeResult == 0);
      return tmNow;
#endif
   }

   string Watch::TimeZone(const tm& tmValue) const
   {
      char timeZoneChars[128];
      strftime(timeZoneChars, sizeof(timeZoneChars), "%Z", &tmValue);
      const string timeZone(timeZoneChars);
      return timeZone;
   }

   unsigned short Watch::SecondsSince1970CastToUnsignedShort() const
   {
      const long long secondsSince1970
         = std::chrono::system_clock::now().time_since_epoch().count();
      const unsigned short secondsSince1970CastToUnsignedShort
         = static_cast<unsigned short>(secondsSince1970);
      return secondsSince1970CastToUnsignedShort;
   }

   const char* Watch::TMWeekDayToWeekDayString(int tm_wday)
   {
      switch (tm_wday)
      {
      case 0: return "Sunday";
      case 1: return "Monday";
      case 2: return "Tuesday";
      case 3: return "Wednesday";
      case 4: return "Thursday";
      case 5: return "Friday";
      case 6: return "Saturday";
      default: throw out_of_range("Invalid tm_wday: " + to_string(tm_wday));
      }
   }

   const char* Watch::TMMonthToMonthString(int tm_mon)
   {
      switch (tm_mon)
      {
      case 0: return "January";
      case 1: return "February";
      case 2: return "March";
      case 3: return "April";
      case 4: return "May";
      case 5: return "June";
      case 6: return "July";
      case 7: return "August";
      case 8: return "September";
      case 9: return "October";
      case 10: return "November";
      case 11: return "December";
      default: throw out_of_range("Invalid tm_mon: " + to_string(tm_mon));
      }
   }
}
