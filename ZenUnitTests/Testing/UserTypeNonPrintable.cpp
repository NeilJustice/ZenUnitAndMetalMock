#include "pch.h"
#include "UserTypeNonPrintable.h"

UserTypeNonPrintable::UserTypeNonPrintable() noexcept = default;

UserTypeNonPrintable::UserTypeNonPrintable(int x) noexcept
   : x(x)
{
}

bool operator<(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right) noexcept
{
   const bool isLessThan = left.x < right.x;
   return isLessThan;
}

bool operator==(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right) noexcept
{
   const bool isEqual = left.x == right.x;
   return isEqual;
}

namespace ZenUnit
{
   void Equalizer<UserTypeNonPrintable>::
   AssertEqual(const UserTypeNonPrintable& expected, const UserTypeNonPrintable& actual)
   {
      ARE_EQUAL(expected.x, actual.x);
   }
}
