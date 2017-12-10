#pragma once

struct UserTypeNonPrintable
{
   int x = 0;
   UserTypeNonPrintable() noexcept;
   explicit UserTypeNonPrintable(int x) noexcept;

   friend bool operator<(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right) noexcept;
   friend bool operator==(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right) noexcept;
};

namespace ZenUnit
{
   template<>
   struct Equalizer<UserTypeNonPrintable>
   {
      static void AssertEqual(const UserTypeNonPrintable& expected, const UserTypeNonPrintable& actual);
   };
}
