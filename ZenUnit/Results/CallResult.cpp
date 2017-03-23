#include "pch.h"
#include "CallResult.h"
#include "Macros/ARE_EQUAL.h"

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
      , exceptionTypeName(nullptr)
   {
   }

   void CallResult::Assign(const CallResult& callResult)
   {
      *this = callResult;
   }
}

void ZenUnitEqualizer<ZenUnit::CallResult>::
AssertEqual(
   const ZenUnit::CallResult& expectedCallResult, 
   const ZenUnit::CallResult& actualCallResult)
{
   ARE_EQUAL(expectedCallResult.testPhase, actualCallResult.testPhase);
   ARE_EQUAL(expectedCallResult.testOutcome, actualCallResult.testOutcome);
   ARE_EQUAL(expectedCallResult.milliseconds, actualCallResult.milliseconds);
   ARE_EQUAL(expectedCallResult.anomaly, actualCallResult.anomaly);
   ARE_EQUAL(expectedCallResult.exceptionTypeName, actualCallResult.exceptionTypeName);
   ARE_EQUAL(expectedCallResult.exceptionWhat, actualCallResult.exceptionWhat);
}
