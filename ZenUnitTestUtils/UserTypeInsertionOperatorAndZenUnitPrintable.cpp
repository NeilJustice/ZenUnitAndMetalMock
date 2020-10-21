#include "pch.h"
#include "ZenUnitTestUtils/UserTypeInsertionOperatorAndZenUnitPrintable.h"

namespace ZenUnit
{
   void Printer<UserTypeInsertionOperatorAndZenUnitPrintable>::Print(ostream& os, const UserTypeInsertionOperatorAndZenUnitPrintable&)
   {
      os << "UserTypeInsertionOperatorAndZenUnitPrintable";
   }
}
