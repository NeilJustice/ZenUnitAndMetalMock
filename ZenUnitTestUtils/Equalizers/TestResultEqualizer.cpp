#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/CallResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestResult>::AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult)
   {
      ARE_EQUAL(expectedTestResult.fullTestName, actualTestResult.fullTestName);
      ARE_EQUAL(expectedTestResult.constructorCallResult, actualTestResult.constructorCallResult);
      ARE_EQUAL(expectedTestResult.startupCallResult, actualTestResult.startupCallResult);
      ARE_EQUAL(expectedTestResult.testBodyCallResult, actualTestResult.testBodyCallResult);
      ARE_EQUAL(expectedTestResult.cleanupCallResult, actualTestResult.cleanupCallResult);
      ARE_EQUAL(expectedTestResult.destructorCallResult, actualTestResult.destructorCallResult);
      ARE_EQUAL(expectedTestResult.responsibleCallResultField, actualTestResult.responsibleCallResultField);
      ARE_EQUAL(expectedTestResult.testOutcome, actualTestResult.testOutcome);
      ARE_EQUAL(expectedTestResult.testCaseNumber, actualTestResult.testCaseNumber);
      ARE_EQUAL(expectedTestResult.microseconds, actualTestResult.microseconds);
   }
}
