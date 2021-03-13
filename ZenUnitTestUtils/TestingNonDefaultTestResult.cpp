#include "pch.h"
#include "ZenUnitTestUtils/TestingNonDefaultTestResult.h"

namespace ZenUnit
{
   const TestResult TestingNonDefaultTestResult() noexcept
   {
      const FullTestName fullTestName("Non", "Default", 0);
      TestResult constructorFail = TestResult::ConstructorFail(fullTestName, TestPhaseResult());
      return constructorFail;
   }
}
