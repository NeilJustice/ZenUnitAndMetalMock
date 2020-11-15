#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"

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
      ARE_EQUAL(expectedTestResult.totalTestCases, actualTestResult.totalTestCases);
      ARE_EQUAL(expectedTestResult.microseconds, actualTestResult.microseconds);
   }

   TestResult TestableRandomTestResult(const RandomGenerator* randomGenerator)
   {
      TestResult randomTestResult;
      randomTestResult.fullTestName = ZenUnit::Random<FullTestName>();
      randomTestResult.constructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.startupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.testBodyTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.cleanupTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.destructorTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      randomTestResult.responsibleTestPhaseResultField = nullptr;
      randomTestResult.testOutcome = static_cast<TestOutcome>(randomGenerator->Enum(static_cast<int>(TestOutcome::MaxValue)));
      randomTestResult.microseconds = randomGenerator->LongLong();
      randomTestResult.testCaseNumber = randomGenerator->SizeT();
      randomTestResult.totalTestCases = randomGenerator->SizeT();
      return randomTestResult;
   }

   template<>
   TestResult Random()
   {
      return TestableRandomTestResult(RandomGenerator::Instance());
   }
}
