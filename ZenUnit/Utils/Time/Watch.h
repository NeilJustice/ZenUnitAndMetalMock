#pragma once

namespace ZenUnit
{
   class Watch
   {
   public:
      virtual std::string TimeZoneDateTimeNow() const;
      virtual unsigned short SecondsSince1970CastToUnsignedShort() const;
      virtual ~Watch() = default;
   private:
      virtual tm TMNow() const;
      virtual std::string TimeZone(const tm& tmValue) const;
      static const char* TMWeekDayToWeekDayString(int tm_wday);
      static const char* TMMonthToMonthString(int tm_mon);
   };
}
