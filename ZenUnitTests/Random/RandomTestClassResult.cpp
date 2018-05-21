#include "pch.h"
#include "ZenUnitTests/Random/RandomTestClassResult.h"
#include "ZenUnitTests/Random/RandomTestResult.h"

namespace ZenUnit
{
   template<>
   TestClassResult Random<TestClassResult>()
   {
      TestClassResult randomTestClassResult;
      const vector<TestResult> randomTestResults = { ZenUnit::Random<TestResult>() };
      randomTestClassResult.AddTestResults(randomTestResults);
      return randomTestClassResult;
   }
}
