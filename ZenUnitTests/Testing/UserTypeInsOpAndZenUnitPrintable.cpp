#include "pch.h"
#include "UserTypeInsOpAndZenUnitPrintable.h"

namespace ZenUnit
{
   void Printer<UserTypeInsOpAndZenUnitPrintable>::Print(
      ostream& os, const UserTypeInsOpAndZenUnitPrintable&)
   {
      os << "UserTypeInsOpAndZenUnitPrintable";
   }
}
