#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomTestPhaseResultTests)
   AFACT(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   AFACT(RandomTestPhaseResult_DoesNotThrowException)
   EVIDENCE

   TEST(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const int testPhaseInt = ZenUnit::Random<int>();
      const int testOutcomeInt = ZenUnit::Random<int>();
      randomGeneratorMock.EnumMock.ReturnValues(testPhaseInt, testOutcomeInt);

      const long long microseconds = randomGeneratorMock.LongLongMock.ReturnRandom();
      //
      const TestPhaseResult randomTestPhaseResult = TestableRandomTestPhaseResult(randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.EnumMock.CalledAsFollows(
      {
         static_cast<int>(TestPhase::MaxValue),
         static_cast<int>(TestOutcome::MaxValue)
      }));
      METALMOCK(randomGeneratorMock.LongLongMock.CalledOnce());
      TestPhaseResult expectedRandomTestPhaseResult;
      expectedRandomTestPhaseResult.testPhase = static_cast<TestPhase>(testPhaseInt);
      expectedRandomTestPhaseResult.testOutcome = static_cast<TestOutcome>(testOutcomeInt);
      expectedRandomTestPhaseResult.microseconds = microseconds;
      expectedRandomTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedRandomTestPhaseResult, randomTestPhaseResult);
   }

   TEST(RandomTestPhaseResult_DoesNotThrowException)
   {
      ZenUnit::Random<TestPhaseResult>();
   }

   RUN_TESTS(RandomTestPhaseResultTests)
}
