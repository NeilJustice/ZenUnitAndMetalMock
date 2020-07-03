#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestRunResultEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestRunResult>::AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult)
   {
      INDEXABLES_ARE_EQUAL(expectedTestRunResult._skippedTestClassNamesAndSkipReasons, actualTestRunResult._skippedTestClassNamesAndSkipReasons);
      INDEXABLES_ARE_EQUAL(expectedTestRunResult._skippedFullTestNamesAndSkipReasons, actualTestRunResult._skippedFullTestNamesAndSkipReasons);
      INDEXABLES_ARE_EQUAL(expectedTestRunResult._testClassResults, actualTestRunResult._testClassResults);
      ARE_EQUAL(expectedTestRunResult._numberOfFailedTestCases, actualTestRunResult._numberOfFailedTestCases);
   }
}
