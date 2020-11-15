#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestRunResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestRunResult>::AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult)
   {
      ARE_EQUAL(expectedTestRunResult._numberOfFailedTestCases, actualTestRunResult._numberOfFailedTestCases);
      VECTORS_ARE_EQUAL(expectedTestRunResult._skippedTestClassNamesAndSkipReasons, actualTestRunResult._skippedTestClassNamesAndSkipReasons);
      VECTORS_ARE_EQUAL(expectedTestRunResult._skippedFullTestNamesAndSkipReasons, actualTestRunResult._skippedFullTestNamesAndSkipReasons);
      VECTORS_ARE_EQUAL(expectedTestRunResult._testClassResults, actualTestRunResult._testClassResults);
   }
}
