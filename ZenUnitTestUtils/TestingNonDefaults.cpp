#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/TestingNonDefaults.h"

namespace ZenUnit
{
   TestResult TestingNonDefaultTestResult() noexcept
   {
      const FullTestName fullTestName("Non", "Default", 0);
      TestResult constructorFailTestResult = TestResult::ConstructorFail(fullTestName, TestPhaseResult(), 0);
      return constructorFailTestResult;
   }

   TestClassResult TestingNonDefaultTestClassResult()
   {
      TestClassResult testClassResult;
      TestResult randomTestResult = ZenUnit::Random<TestResult>();
      testClassResult.AddTestResult(randomTestResult);
      return testClassResult;
   }
}
