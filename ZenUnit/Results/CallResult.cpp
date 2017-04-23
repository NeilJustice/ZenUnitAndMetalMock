#include "pch.h"
#include "CallResult.h"
#include "Macros/ARE_EQUAL.h"
#include "Macros/IS_FALSE.h"
#include "Macros/POINTEES_EQUAL.h"
#include "Results/AnomalyOrException.h"

namespace ZenUnit
{
   CallResult::CallResult()
      : CallResult(TestPhase::Unset)
   {
   }

   CallResult::CallResult(TestPhase testPhase)
      : testPhase(testPhase)
      , testOutcome(TestOutcome::Success)
      , milliseconds(0)
   {
   }
}

void ZenUnitEqualizer<ZenUnit::CallResult>::AssertEqual(
   const ZenUnit::CallResult& expectedCallResult,
   const ZenUnit::CallResult& actualCallResult)
{
   ARE_EQUAL(expectedCallResult.testPhase, actualCallResult.testPhase);
   ARE_EQUAL(expectedCallResult.testOutcome, actualCallResult.testOutcome);
   ARE_EQUAL(expectedCallResult.milliseconds, actualCallResult.milliseconds);
   POINTEES_EQUAL(expectedCallResult.anomalyOrException, actualCallResult.anomalyOrException);
}
