#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestPhaseResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFullTestName.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>()
   {
      return TestableRandomTestResult(RandomGenerator());
   }

   TestResult TestableRandomTestResult(const RandomGenerator& randomGenerator)
   {
      TestResult randomTestResult;
      randomTestResult.fullTestName = ZenUnit::Random<FullTestName>();
      randomTestResult.constructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.startupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.testBodyTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.cleanupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.destructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.responsibleTestPhaseResultField = nullptr;
      randomTestResult.testOutcome = static_cast<TestOutcome>(randomGenerator.Enum(static_cast<int>(TestOutcome::MaxValue)));
      randomTestResult.microseconds = randomGenerator.UnsignedInt();
      randomTestResult.testCaseNumber = randomGenerator.UnsignedLongLong();
      randomTestResult.totalTestCases = randomGenerator.UnsignedLongLong();
      return randomTestResult;
   }
}
