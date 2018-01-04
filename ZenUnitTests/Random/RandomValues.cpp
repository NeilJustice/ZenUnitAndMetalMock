#include "pch.h"
#include "ZenUnitTests/Random/RandomValues.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>()
   {
      TestResult randomTestResult;
      randomTestResult.milliseconds = ZenUnit::Random<unsigned>();
      return randomTestResult;
   }

   template<>
   TestClassResult Random<TestClassResult>()
   {
      TestClassResult randomTestClassResult;
      const vector<TestResult> randomTestResults = { ZenUnit::Random<TestResult>() };
      randomTestClassResult.AddTestResults(randomTestResults);
      return randomTestClassResult;
   }
}
