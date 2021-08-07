#include "pch.h"
#include "ZenUnitTestUtils/OnlyZenUnitPrintableUserType.h"

namespace ZenUnit
{
   void Printer<OnlyZenUnitPrintableUserType>::Print(ostream& os, const OnlyZenUnitPrintableUserType&)
   {
      os << "OnlyZenUnitPrintableUserType";
   }
}
