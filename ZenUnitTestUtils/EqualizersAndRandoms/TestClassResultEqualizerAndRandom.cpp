#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestClassResult>::AssertEqual(
      const TestClassResult& expectedTestClassResult, const TestClassResult& actualTestClassResult)
   {
      FIELDS_ARE_EQUAL(expectedTestClassResult, actualTestClassResult, _testResults);
   }

   template<>
   TestClassResult Random()
   {
      TestClassResult randomTestClassResult;
      const vector<TestResult> randomNonEmptyTestResults = ZenUnit::RandomNonEmptyVector<TestResult>();
      randomTestClassResult.AddTestResults(randomNonEmptyTestResults);
      return randomTestClassResult;
   }
}
