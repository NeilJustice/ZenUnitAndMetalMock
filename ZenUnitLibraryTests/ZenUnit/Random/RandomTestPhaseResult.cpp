#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestPhaseResult.h"

namespace ZenUnit
{
   template<>
   TestPhaseResult Random<TestPhaseResult>()
   {
      TestPhaseResult randomTestPhaseResult;
      randomTestPhaseResult.testPhase = ZenUnit::RandomNon0Enum<TestPhase>(TestPhase::MaxValue);
      randomTestPhaseResult.testOutcome = ZenUnit::RandomNon0Enum<TestOutcome>(TestOutcome::MaxValue);
      randomTestPhaseResult.microseconds = ZenUnit::Random<unsigned>();
      randomTestPhaseResult.anomalyOrException = nullptr;
      return randomTestPhaseResult;
   }
}
