#include "pch.h"
#include "ZenUnitLibraryTests/Random/RandomTestResult.h"
#include "ZenUnitLibraryTests/Random/RandomTestPhaseResult.h"
#include "ZenUnitLibraryTests/Random/RandomFullTestName.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>()
   {
      TestResult randomTestResult;
      randomTestResult.fullTestName = ZenUnit::Random<FullTestName>();
      randomTestResult.constructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.startupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.testBodyTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.cleanupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.destructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.responsibleTestPhaseResultField = nullptr;
      randomTestResult.testOutcome = ZenUnit::RandomNon0Enum<TestOutcome>(TestOutcome::MaxValue);
      randomTestResult.microseconds = ZenUnit::RandomNon0<unsigned>();
      randomTestResult.testCaseNumber = ZenUnit::RandomNon0<size_t>();
      randomTestResult.totalTestCases = ZenUnit::RandomNon0<size_t>();
      return randomTestResult;
   }
}
