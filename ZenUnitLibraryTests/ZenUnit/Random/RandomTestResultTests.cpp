#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"
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

      const int testOutcomeInt = ZenUnit::RandomBetween<int>(0, numeric_limits<unsigned char>::max());
      randomGeneratorMock.EnumMock.Return(testOutcomeInt);

      const unsigned microseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const size_t totalTestCases = ZenUnit::Random<size_t>();
      randomGeneratorMock.SizeTMock.ReturnValues(testCaseNumber, totalTestCases);
      //
      const TestResult randomTestResult = TestableRandomTestResult(randomGeneratorMock);
      //
      ZENMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(TestOutcome::MaxValue)));
      ZENMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      ZENMOCK(randomGeneratorMock.SizeTMock.CalledNTimes(2));

      IS_NOT_DEFAULT_VALUE(randomTestResult.fullTestName);
      IS_NOT_DEFAULT_VALUE(randomTestResult.constructorTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.startupTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.testBodyTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.cleanupTestPhaseResult);
      IS_NOT_DEFAULT_VALUE(randomTestResult.destructorTestPhaseResult);
      POINTER_IS_NULL(randomTestResult.responsibleTestPhaseResultField);
      ARE_EQUAL(testOutcomeInt, static_cast<int>(randomTestResult.testOutcome));
      ARE_EQUAL(microseconds, randomTestResult.microseconds);
      ARE_EQUAL(testCaseNumber, randomTestResult.testCaseNumber);
      ARE_EQUAL(totalTestCases, randomTestResult.totalTestCases);
   }

   RUN_TESTS(RandomTestResultTests)
}
