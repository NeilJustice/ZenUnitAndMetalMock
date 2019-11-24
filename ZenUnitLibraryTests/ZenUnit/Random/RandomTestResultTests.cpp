#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(RandomTestResultTests)
   AFACT(RandomTestResult_CodeCoverage)
   AFACT(TestableRandomTestResult_ReturnsTestResultWithAllRandomFields)
   EVIDENCE

   TEST(RandomTestResult_CodeCoverage)
   {
      const TestResult randomTestResult = ZenUnit::Random<TestResult>();
   }

   TEST(TestableRandomTestResult_ReturnsTestResultWithAllRandomFields)
   {
      ZenMock::RandomGeneratorMock randomGeneratorMock;

      const int testOutcomeInt = randomGeneratorMock.EnumMock.ReturnRandom();

      const unsigned microseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();

      const unsigned long long testCaseNumber = ZenUnit::Random<unsigned long long>();
      const unsigned long long totalTestCases = ZenUnit::Random<unsigned long long>();
      randomGeneratorMock.UnsignedLongLongMock.ReturnValues(testCaseNumber, totalTestCases);
      //
      const TestResult randomTestResult = TestableRandomTestResult(randomGeneratorMock);
      //
      ZENMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(TestOutcome::MaxValue)));
      ZENMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      ZENMOCK(randomGeneratorMock.UnsignedLongLongMock.CalledNTimes(2));
      TestResult expectedRandomTestResult;
      //expectedRandomTestResult.fullTestName = fullTestName;
      //expectedRandomTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
      //expectedRandomTestResult.startupTestPhaseResult = startupTestPhaseResult;
      //expectedRandomTestResult.testBodyTestPhaseResult = testBodyTestPhaseResult;
      //expectedRandomTestResult.cleanupTestPhaseResult = cleanupTestPhaseResult;
      //expectedRandomTestResult.destructorTestPhaseResult = destructorTestPhaseResult;
      expectedRandomTestResult.responsibleTestPhaseResultField = nullptr;
      expectedRandomTestResult.testOutcome = static_cast<TestOutcome>(testOutcomeInt);
      expectedRandomTestResult.microseconds = microseconds;
      expectedRandomTestResult.testCaseNumber = testCaseNumber;
      expectedRandomTestResult.totalTestCases = totalTestCases;
      ARE_EQUAL(expectedRandomTestResult, randomTestResult);
   }

   RUN_TESTS(RandomTestResultTests)
}
