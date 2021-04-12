#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestResultEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomTestResult_ReturnsTestResultWithAllRandomFields)
   AFACT(RandomTestResult_DoesNotThrowException)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, fullTestName, ZenUnit::Random<FullTestName>());
      TestPhaseResult nonDefaultTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
      nonDefaultTestPhaseResult.microseconds = ZenUnit::RandomNon0<unsigned>();
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, constructorTestPhaseResult, nonDefaultTestPhaseResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, startupTestPhaseResult, nonDefaultTestPhaseResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, testBodyTestPhaseResult, nonDefaultTestPhaseResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, cleanupTestPhaseResult, nonDefaultTestPhaseResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, destructorTestPhaseResult, nonDefaultTestPhaseResult);
      TestPhaseResult TestResult::*testPhaseResultMemberFieldPointer = &TestResult::constructorTestPhaseResult;
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, responsibleTestPhaseResultField, testPhaseResultMemberFieldPointer);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, testOutcome, ZenUnit::RandomNon0Enum<TestOutcome>(TestOutcome::MaxValue));
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, testCaseNumber, ZenUnit::RandomNotEqualToValue<size_t>(numeric_limits<size_t>::max()));
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, totalTestCases, ZenUnit::RandomNon0<size_t>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestResult, microseconds, ZenUnit::RandomNon0<unsigned>());
   }

   TEST(TestableRandomTestResult_ReturnsTestResultWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const TestOutcome testOutcome = static_cast<TestOutcome>(randomGeneratorMock.EnumMock.ReturnRandom());

      const unsigned microseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const size_t totalTestCases = ZenUnit::Random<size_t>();
      randomGeneratorMock.SizeTMock.ReturnValues(testCaseNumber, totalTestCases);
      //
      const TestResult randomTestResult = TestableRandomTestResult(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(TestOutcome::MaxValue)));
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      METALMOCK(randomGeneratorMock.SizeTMock.CalledNTimes(2));

      //IS_NOT_DEFAULT_VALUE(randomTestResult.fullTestName);
      //IS_NOT_DEFAULT_VALUE(randomTestResult.constructorTestPhaseResult);
      //IS_NOT_DEFAULT_VALUE(randomTestResult.startupTestPhaseResult);
      //IS_NOT_DEFAULT_VALUE(randomTestResult.testBodyTestPhaseResult);
      //IS_NOT_DEFAULT_VALUE(randomTestResult.cleanupTestPhaseResult);
      //IS_NOT_DEFAULT_VALUE(randomTestResult.destructorTestPhaseResult);
      IS_NULLPTR(randomTestResult.responsibleTestPhaseResultField);
      ARE_EQUAL(testOutcome, randomTestResult.testOutcome);
      ARE_EQUAL(microseconds, randomTestResult.microseconds);
      ARE_EQUAL(testCaseNumber, randomTestResult.testCaseNumber);
      ARE_EQUAL(totalTestCases, randomTestResult.totalTestCases);
   }

   TEST(RandomTestResult_DoesNotThrowException)
   {
      const TestResult randomTestResult = ZenUnit::Random<TestResult>();
   }

   RUN_TESTS(TestResultEqualizerAndRandomTests)
}
