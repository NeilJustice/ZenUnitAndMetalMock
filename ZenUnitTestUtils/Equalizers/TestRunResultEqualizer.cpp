#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestRunResultEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestRunResult>::AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult)
   {
      VECTORS_EQUAL(expectedTestRunResult._skippedTestClassNamesAndReasons, actualTestRunResult._skippedTestClassNamesAndReasons);
      VECTORS_EQUAL(expectedTestRunResult._skippedFullTestNamesAndReasons, actualTestRunResult._skippedFullTestNamesAndReasons);
      VECTORS_EQUAL(expectedTestRunResult._testClassResults, actualTestRunResult._testClassResults);
      ARE_EQUAL(expectedTestRunResult._numberOfFailedTestCases, actualTestRunResult._numberOfFailedTestCases);
   }
}
