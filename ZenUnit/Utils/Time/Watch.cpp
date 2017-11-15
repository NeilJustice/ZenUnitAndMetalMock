//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Time/Watch.h"
#include <iomanip>

namespace ZenUnit
{
   // Returns now in format "Monday January 1, 2016 at 00:00:00 <Timezone>"
   INLINE std::string Watch::TimeZoneDateTimeNow() const
   {
      const tm tmNow = TMNow();
      std::ostringstream builder;
      const char* const weekDayString = TMWeekDayToWeekDayString(tmNow.tm_wday);
      const char* const monthString = TMMonthToMonthString(tmNow.tm_mon);
      const std::string timeZone = TimeZone(tmNow);
      builder << std::setw(2) << std::setfill('0') << tmNow.tm_hour << ':'
              << std::setw(2) << std::setfill('0') << tmNow.tm_min << ':'
              << std::setw(2) << std::setfill('0') << tmNow.tm_sec << ' '
              << timeZone << " on " << weekDayString << ' ' << monthString << ' ' << tmNow.tm_mday << ", " << (tmNow.tm_year + 1900);
      const std::string weekdayDateTimeZoneNow = builder.str();
      return weekdayDateTimeZoneNow;
   }

   INLINE tm Watch::TMNow() const
   {
      const std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now();
#ifdef __linux__
      tm* tmNow = nullptr;
      long nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
      tmNow = localtime(&nowTimeT);
      return *tmNow;
#elif _WIN32
      const __time64_t nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
      tm tmNow;
      const errno_t localtimeResult = localtime_s(&tmNow, &nowTimeT);
      assert_true(localtimeResult == 0);
      return tmNow;
#endif
   }

   INLINE std::string Watch::TimeZone(const tm& tmValue) const
   {
      char timeZoneChars[128];
      strftime(timeZoneChars, sizeof(timeZoneChars), "%Z", &tmValue);
      const std::string timeZone(timeZoneChars);
      return timeZone;
   }

   INLINE unsigned short Watch::SecondsSince1970CastToUnsignedShort() const
   {
      const long long secondsSince1970
         = std::chrono::system_clock::now().time_since_epoch().count();
      const unsigned short secondsSince1970CastToUnsignedShort
         = static_cast<unsigned short>(secondsSince1970);
      return secondsSince1970CastToUnsignedShort;
   }

   INLINE const char* Watch::TMWeekDayToWeekDayString(int tm_wday)
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
      default: throw std::out_of_range("Invalid tm_wday: " + std::to_string(tm_wday));
      }
   }

   INLINE const char* Watch::TMMonthToMonthString(int tm_mon)
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
      default: throw std::out_of_range("Invalid tm_mon: " + std::to_string(tm_mon));
      }
   }
}
