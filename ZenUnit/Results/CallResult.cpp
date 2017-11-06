#include "pch.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/IS_FALSE.h"
#include "ZenUnit/Macros/POINTEES_EQUAL.h"
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Results/CallResult.h"

namespace ZenUnit
{
   inline CallResult::CallResult()
      : CallResult(TestPhase::Unset)
   {
   }

   inline CallResult::CallResult(TestPhase testPhase)
      : testPhase(testPhase)
      , testOutcome(TestOutcome::Success)
      , milliseconds(0)
   {
   }
}

inline void ZenUnitEqualizer<ZenUnit::CallResult>::AssertEqual(
   const ZenUnit::CallResult& expectedCallResult,
   const ZenUnit::CallResult& actualCallResult)
{
   ARE_EQUAL(expectedCallResult.testPhase, actualCallResult.testPhase);
   ARE_EQUAL(expectedCallResult.testOutcome, actualCallResult.testOutcome);
   ARE_EQUAL(expectedCallResult.milliseconds, actualCallResult.milliseconds);
   POINTEES_EQUAL(expectedCallResult.anomalyOrException, actualCallResult.anomalyOrException);
}
