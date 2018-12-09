#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestResult>::AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult)
   {
      ARE_EQUAL(expectedTestResult.fullTestName, actualTestResult.fullTestName);
      ARE_EQUAL(expectedTestResult.constructorTestPhaseResult, actualTestResult.constructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult.startupTestPhaseResult, actualTestResult.startupTestPhaseResult);
      ARE_EQUAL(expectedTestResult.testBodyTestPhaseResult, actualTestResult.testBodyTestPhaseResult);
      ARE_EQUAL(expectedTestResult.cleanupTestPhaseResult, actualTestResult.cleanupTestPhaseResult);
      ARE_EQUAL(expectedTestResult.destructorTestPhaseResult, actualTestResult.destructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult.responsibleTestPhaseResultField, actualTestResult.responsibleTestPhaseResultField);
      ARE_EQUAL(expectedTestResult.testOutcome, actualTestResult.testOutcome);
      ARE_EQUAL(expectedTestResult.testCaseNumber, actualTestResult.testCaseNumber);
      ARE_EQUAL(expectedTestResult.microseconds, actualTestResult.microseconds);
   }
}
