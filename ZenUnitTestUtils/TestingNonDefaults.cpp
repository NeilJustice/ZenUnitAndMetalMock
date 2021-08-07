#include "pch.h"
#include "ZenUnitTestUtils/TestingNonDefaults.h"

namespace ZenUnit
{
   TestResult TestingNonDefaultTestResult() noexcept
   {
      const FullTestName fullTestName("Non", "Default", 0);
      TestResult constructorFailTestResult = TestResult::ConstructorFail(fullTestName, TestPhaseResult());
      return constructorFailTestResult;
   }

   TestClassResult TestingNonDefaultTestClassResult()
   {
      TestClassResult testClassResult;
      testClassResult._testResults.resize(1);
      return testClassResult;
   }
}
