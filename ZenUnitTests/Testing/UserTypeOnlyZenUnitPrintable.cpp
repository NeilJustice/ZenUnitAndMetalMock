#include "pch.h"
#include "UserTypeOnlyZenUnitPrintable.h"

namespace ZenUnit
{
   void Printer<UserTypeOnlyZenUnitPrintable>::
      Print(ostream& os, const UserTypeOnlyZenUnitPrintable&)
   {
      os << "UserTypeOnlyZenUnitPrintable";
   }
}
