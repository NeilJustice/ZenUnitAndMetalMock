#include "pch.h"

namespace ZenUnit
{
   TESTS(TestPhaseResultEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   AFACT(RandomTestPhaseResult_CodeCoverage)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestPhaseResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestPhaseResult, testPhase, ZenUnit::RandomNon0Enum<TestPhase>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestPhaseResult, testOutcome, TestOutcome::Anomaly);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestPhaseResult, elapsedMicroseconds, ZenUnit::RandomNon0<unsigned>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestPhaseResult, anomalyOrException, make_shared<AnomalyOrException>(ZenUnit::Random<AnomalyOrException>()));
   }

   TEST(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const int testPhaseInt = ZenUnit::Random<int>();
      const int testOutcomeInt = ZenUnit::Random<int>();
      randomGeneratorMock.EnumMock.ReturnValues(testPhaseInt, testOutcomeInt);

      const unsigned elapsedMicroseconds = randomGeneratorMock.UnsignedMock.ReturnRandom();
      //
      const TestPhaseResult randomTestPhaseResult = TestableRandomTestPhaseResult(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.EnumMock.CalledNTimes(2));
      METALMOCKTHEN(randomGeneratorMock.EnumMock.CalledWith(static_cast<int>(TestPhase::MaxValue))).Then(
      METALMOCKTHEN(randomGeneratorMock.EnumMock.CalledWith(static_cast<int>(TestOutcome::MaxValue)))).Then(
      METALMOCKTHEN(randomGeneratorMock.UnsignedMock.CalledOnce()));
      TestPhaseResult expectedRandomTestPhaseResult{};
      expectedRandomTestPhaseResult.testPhase = static_cast<TestPhase>(testPhaseInt);
      expectedRandomTestPhaseResult.testOutcome = static_cast<TestOutcome>(testOutcomeInt);
      expectedRandomTestPhaseResult.elapsedMicroseconds = elapsedMicroseconds;
      expectedRandomTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedRandomTestPhaseResult, randomTestPhaseResult);
   }

   TEST(RandomTestPhaseResult_CodeCoverage)
   {
      ZenUnit::Random<TestPhaseResult>();
   }

   RUN_TESTS(TestPhaseResultEqualizerAndRandomTests)
}
