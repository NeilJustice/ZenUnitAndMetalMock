#include "pch.h"
#include "NoOpTestClassRunner.h"

namespace ZenUnit
{
   const char* NoOpTestClassRunner::TestClassName() const
   {
      return "NoOpTestClassRunner";
   }

   size_t NoOpTestClassRunner::NumberOfTestCases() const
   {
      return 0;
   }

   TestClassResult NoOpTestClassRunner::RunTests()
   {
      return TestClassResult();
   }
}
