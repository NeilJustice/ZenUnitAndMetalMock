#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestPhaseResult>::AssertEqual(const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult)
   {
      ARE_EQUAL(expectedTestPhaseResult.testPhase, actualTestPhaseResult.testPhase);
      ARE_EQUAL(expectedTestPhaseResult.testOutcome, actualTestPhaseResult.testOutcome);
      ARE_EQUAL(expectedTestPhaseResult.microseconds, actualTestPhaseResult.microseconds);
      POINTEES_ARE_EQUAL(expectedTestPhaseResult.anomalyOrException, actualTestPhaseResult.anomalyOrException);
   }

   template<>
   TestPhaseResult Random<TestPhaseResult>()
   {
      return TestableRandomTestPhaseResult(RandomGenerator());
   }

   TestPhaseResult TestableRandomTestPhaseResult(const RandomGenerator& randomGenerator)
   {
      TestPhaseResult randomTestPhaseResult;
      randomTestPhaseResult.testPhase = static_cast<TestPhase>(randomGenerator.Enum(static_cast<int>(TestPhase::MaxValue)));
      randomTestPhaseResult.testOutcome = static_cast<TestOutcome>(randomGenerator.Enum(static_cast<int>(TestOutcome::MaxValue)));
      randomTestPhaseResult.microseconds = randomGenerator.LongLong();
      randomTestPhaseResult.anomalyOrException = nullptr;
      return randomTestPhaseResult;
   }
}
