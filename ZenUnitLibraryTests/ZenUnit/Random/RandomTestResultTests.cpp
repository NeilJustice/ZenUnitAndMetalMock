#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

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
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const int testOutcomeInt = ZenUnit::RandomBetween<int>(0, numeric_limits<unsigned char>::max());
      randomGeneratorMock.EnumMock.Return(testOutcomeInt);

      const unsigned microseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const size_t totalTestCases = ZenUnit::Random<size_t>();
      randomGeneratorMock.SizeTMock.ReturnValues(testCaseNumber, totalTestCases);
      //
      const TestResult randomTestResult = TestableRandomTestResult(randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(TestOutcome::MaxValue)));
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      METALMOCK(randomGeneratorMock.SizeTMock.CalledNTimes(2));

      IS_NOT_DEFAULT_VALUE(randomTestResult.fullTestName);
      IS_NOT_DEFAULT_VALUE(randomTestResult.constructorTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.startupTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.testBodyTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.cleanupTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.destructorTestPhaseResult);
      IS_NULLPTR(randomTestResult.responsibleTestPhaseResultField);
      ARE_EQUAL(testOutcomeInt, static_cast<int>(randomTestResult.testOutcome));
      ARE_EQUAL(microseconds, randomTestResult.microseconds);
      ARE_EQUAL(testCaseNumber, randomTestResult.testCaseNumber);
      ARE_EQUAL(totalTestCases, randomTestResult.totalTestCases);
   }

   RUN_TESTS(RandomTestResultTests)
}
