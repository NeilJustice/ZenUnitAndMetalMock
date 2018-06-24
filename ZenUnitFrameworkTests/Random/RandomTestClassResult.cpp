#include "pch.h"
#include "ZenUnitFrameworkTests/Random/RandomTestClassResult.h"
#include "ZenUnitFrameworkTests/Random/RandomTestResult.h"

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
