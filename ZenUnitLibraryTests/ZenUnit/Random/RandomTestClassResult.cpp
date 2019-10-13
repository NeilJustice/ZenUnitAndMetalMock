#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"

namespace ZenUnit
{
   template<>
   TestClassResult Random<TestClassResult>()
   {
      TestClassResult randomTestClassResult;
      const vector<TestResult> randomTestResults = ZenUnit::RandomVector<TestResult>();
      randomTestClassResult.AddTestResults(randomTestResults);
      return randomTestClassResult;
   }
}
