#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestPhaseResult.h"

namespace ZenUnit
{
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
