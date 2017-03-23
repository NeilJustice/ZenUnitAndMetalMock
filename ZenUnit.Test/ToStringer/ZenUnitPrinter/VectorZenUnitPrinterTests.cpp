#include "pch.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/VectorZenUnitPrinter.h"
#include "Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   TESTS(VectorZenUnitPrinterTests)
   SPEC(Print_PrintsPlaceholder)
   SPECEND

   TEST(Print_PrintsPlaceholder)
   {
      ostringstream oss;
      ZenUnitPrinter<vector<int>>::Print(oss, {});
      ARE_EQUAL("vector<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<vector<int, CustomAllocator<int>>>::Print(oss, {});
      ARE_EQUAL("vector<T>", oss.str());
   }

   }; RUN(VectorZenUnitPrinterTests)
}
