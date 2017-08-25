#include "pch.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/VectorZenUnitPrinter.h"
#include "ZenUnitTests/Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   TESTS(VectorZenUnitPrinterTests)
   FACT(ZenUnitPrinter_Print_PrintsPlaceholderText)
   EVIDENCE

   TEST(ZenUnitPrinter_Print_PrintsPlaceholderText)
   {
      ostringstream oss;
      ZenUnitPrinter<vector<int>>::Print(oss, {});
      ARE_EQUAL("vector<T>", oss.str());
      oss = ostringstream();

      ZenUnitPrinter<vector<int, CustomAllocator<int>>>::Print(oss, {});
      ARE_EQUAL("vector<T>", oss.str());
   }

   }; RUNTESTS(VectorZenUnitPrinterTests)
}
