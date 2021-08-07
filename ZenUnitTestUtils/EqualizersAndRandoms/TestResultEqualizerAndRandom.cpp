#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/ZenUnitTestingRandomGenerator.h"

namespace ZenUnit
{
   void Equalizer<TestResult>::AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult)
   {
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, fullTestName);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, constructorTestPhaseResult);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, startupTestPhaseResult);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, testBodyTestPhaseResult);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, cleanupTestPhaseResult);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, destructorTestPhaseResult);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, responsibleTestPhaseResultField);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, testOutcome);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, testCaseNumber);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, totalTestCases);
      FIELDS_ARE_EQUAL(expectedTestResult, actualTestResult, elapsedMicroseconds);
   }

   TestResult TestableRandomTestResult(const RandomGenerator* randomGenerator, const ZenUnitTestingRandomGenerator* zenUnitTestingRandomGenerator)
   {
      TestResult randomTestResult;
      randomTestResult.fullTestName = zenUnitTestingRandomGenerator->RandomFullTestName();
      randomTestResult.constructorTestPhaseResult = zenUnitTestingRandomGenerator->RandomTestPhaseResult();
      randomTestResult.startupTestPhaseResult = zenUnitTestingRandomGenerator->RandomTestPhaseResult();
      randomTestResult.testBodyTestPhaseResult = zenUnitTestingRandomGenerator->RandomTestPhaseResult();
      randomTestResult.cleanupTestPhaseResult = zenUnitTestingRandomGenerator->RandomTestPhaseResult();
      randomTestResult.destructorTestPhaseResult = zenUnitTestingRandomGenerator->RandomTestPhaseResult();
      randomTestResult.responsibleTestPhaseResultField = nullptr;
      randomTestResult.testOutcome = static_cast<TestOutcome>(randomGenerator->Enum(static_cast<int>(TestOutcome::MaxValue)));
      randomTestResult.elapsedMicroseconds = randomGenerator->UnsignedInt();
      randomTestResult.testCaseNumber = randomGenerator->SizeT();
      randomTestResult.totalTestCases = randomGenerator->SizeT();
      return randomTestResult;
   }

   template<>
   TestResult Random()
   {
      return TestableRandomTestResult(RandomGenerator::Instance(), ZenUnitTestingRandomGenerator::Instance());
   }
}
