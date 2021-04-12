#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestPhaseResult>::AssertEqual(
      const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult)
   {
      ARE_EQUAL(expectedTestPhaseResult.testPhase, actualTestPhaseResult.testPhase);
      ARE_EQUAL(expectedTestPhaseResult.testOutcome, actualTestPhaseResult.testOutcome);
      ARE_EQUAL(expectedTestPhaseResult.elapsedMicroseconds, actualTestPhaseResult.elapsedMicroseconds);
      POINTEES_ARE_EQUAL(expectedTestPhaseResult.anomalyOrException, actualTestPhaseResult.anomalyOrException);
   }

   TestPhaseResult TestableRandomTestPhaseResult(const RandomGenerator* randomGenerator)
   {
      TestPhaseResult randomTestPhaseResult;
      randomTestPhaseResult.testPhase = static_cast<TestPhase>(randomGenerator->Enum(static_cast<int>(TestPhase::MaxValue)));
      randomTestPhaseResult.testOutcome = static_cast<TestOutcome>(randomGenerator->Enum(static_cast<int>(TestOutcome::MaxValue)));
      randomTestPhaseResult.elapsedMicroseconds = randomGenerator->UnsignedInt();
      randomTestPhaseResult.anomalyOrException = nullptr;
      return randomTestPhaseResult;
   }

   template<>
   TestPhaseResult Random<TestPhaseResult>()
   {
      return TestableRandomTestPhaseResult(RandomGenerator::Instance());
   }
}
