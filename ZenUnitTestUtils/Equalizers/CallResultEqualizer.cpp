#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/CallResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/AnomalyOrExceptionEqualizer.h"

namespace ZenUnit
{
   void Equalizer<CallResult>::AssertEqual(const CallResult& expectedCallResult, const CallResult& actualCallResult)
   {
      ARE_EQUAL(expectedCallResult.testPhase, actualCallResult.testPhase);
      ARE_EQUAL(expectedCallResult.testOutcome, actualCallResult.testOutcome);
      ARE_EQUAL(expectedCallResult.microseconds, actualCallResult.microseconds);
      POINTEES_EQUAL(expectedCallResult.anomalyOrException, actualCallResult.anomalyOrException);
   }
}
