#include "pch.h"
#include "ZenUnitTestUtils/DoublyPrintableUserType.h"

namespace ZenUnit
{
   void Printer<DoublyPrintableUserType>::Print(ostream& os, const DoublyPrintableUserType&)
   {
      os << "DoublyPrintableUserType";
   }
}
