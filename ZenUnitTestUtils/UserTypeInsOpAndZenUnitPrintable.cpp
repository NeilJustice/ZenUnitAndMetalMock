#include "pch.h"
#include "ZenUnitTestUtils/UserTypeInsOpAndZenUnitPrintable.h"

namespace ZenUnit
{
   void Printer<UserTypeInsOpAndZenUnitPrintable>::Print(
      ostream& os, const UserTypeInsOpAndZenUnitPrintable&)
   {
      os << "UserTypeInsOpAndZenUnitPrintable";
   }
}
