#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"

namespace ZenUnit
{
   template<>
   TestClassResult Random<TestClassResult>()
   {
      return TestableRandomTestClassResult(RandomGenerator());
   }

   TestClassResult TestableRandomTestClassResult(const RandomGenerator& randomGenerator)
   {
      TestClassResult randomTestClassResult;
      const vector<TestResult> randomTestResults = randomGenerator.NonEmptyVector<TestResult>();
      randomTestClassResult.AddTestResults(randomTestResults);
      return randomTestClassResult;
   }
}
