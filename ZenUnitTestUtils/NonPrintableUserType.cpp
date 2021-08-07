#include "pch.h"
#include "ZenUnitTestUtils/NonPrintableUserType.h"

NonPrintableUserType::NonPrintableUserType(int x)
   : x(x)
{
}

bool operator==(const NonPrintableUserType& left, const NonPrintableUserType& right)
{
   const bool isEqual = left.x == right.x;
   return isEqual;
}

bool operator<(const NonPrintableUserType& left, const NonPrintableUserType& right)
{
   const bool isLessThan = left.x < right.x;
   return isLessThan;
}
