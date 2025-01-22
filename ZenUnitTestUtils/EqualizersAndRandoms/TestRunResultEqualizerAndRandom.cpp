#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestRunResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestRunResult>::AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult)
   {
      FIELDS_ARE_EQUAL(expectedTestRunResult, actualTestRunResult, _numberOfFailedTestCases);
      FIELDS_ARE_EQUAL(expectedTestRunResult, actualTestRunResult, _skippedTestClassNamesAndSkipReasons);
      FIELDS_ARE_EQUAL(expectedTestRunResult, actualTestRunResult, _skippedFullTestNamesAndSkipReasons);
      FIELDS_ARE_EQUAL(expectedTestRunResult, actualTestRunResult, _testClassResults);
   }
}
