#include "pch.h"
#include "ZenUnitLibraryTests/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/Random/RandomTestResult.h"

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
