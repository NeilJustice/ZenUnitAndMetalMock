#include "pch.h"
#include "ZenUnitTestUtils/UserTypeOnlyZenUnitPrintable.h"

namespace ZenUnit
{
   void Printer<UserTypeOnlyZenUnitPrintable>::Print(ostream& os, const UserTypeOnlyZenUnitPrintable&)
   {
      os << "UserTypeOnlyZenUnitPrintable";
   }
}
