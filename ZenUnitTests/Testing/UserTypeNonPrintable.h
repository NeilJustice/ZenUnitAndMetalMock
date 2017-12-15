#pragma once

struct UserTypeNonPrintable
{
   int x = 0;
   UserTypeNonPrintable();
   explicit UserTypeNonPrintable(int x);

   friend bool operator<(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right);
   friend bool operator==(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right);
};

namespace ZenUnit
{
   template<>
   struct Equalizer<UserTypeNonPrintable>
   {
      static void AssertEqual(const UserTypeNonPrintable& expected, const UserTypeNonPrintable& actual);
   };
}
