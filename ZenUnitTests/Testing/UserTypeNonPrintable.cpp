#include "pch.h"
#include "UserTypeNonPrintable.h"

UserTypeNonPrintable::UserTypeNonPrintable() = default;

UserTypeNonPrintable::UserTypeNonPrintable(int x)
   : x(x)
{
}

bool operator<(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right)
{
   const bool isLessThan = left.x < right.x;
   return isLessThan;
}

bool operator==(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right)
{
   const bool isEqual = left.x == right.x;
   return isEqual;
}

void ZenUnitEqualizer<UserTypeNonPrintable>::
AssertEqual(const UserTypeNonPrintable& expected, const UserTypeNonPrintable& actual)
{
   ARE_EQUAL(expected.x, actual.x);
}
