#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestPhaseResult>::AssertEqual(
      const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult)
   {
      FIELDS_ARE_EQUAL(expectedTestPhaseResult, actualTestPhaseResult, testPhase);
      FIELDS_ARE_EQUAL(expectedTestPhaseResult, actualTestPhaseResult, testOutcome);
      FIELDS_ARE_EQUAL(expectedTestPhaseResult, actualTestPhaseResult, elapsedMicroseconds);
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
