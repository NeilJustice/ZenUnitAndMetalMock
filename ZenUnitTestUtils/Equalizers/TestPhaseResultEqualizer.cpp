#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/AnomalyOrExceptionEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestPhaseResult>::AssertEqual(const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult)
   {
      ARE_EQUAL(expectedTestPhaseResult.testPhase, actualTestPhaseResult.testPhase);
      ARE_EQUAL(expectedTestPhaseResult.testOutcome, actualTestPhaseResult.testOutcome);
      ARE_EQUAL(expectedTestPhaseResult.microseconds, actualTestPhaseResult.microseconds);
      POINTEES_ARE_EQUAL(expectedTestPhaseResult.anomalyOrException, actualTestPhaseResult.anomalyOrException);
   }
}
