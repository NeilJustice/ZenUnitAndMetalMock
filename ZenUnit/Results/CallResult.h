#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct AnomalyOrException;

   struct CallResult
   {
      TestPhase testPhase;
      TestOutcome testOutcome;
      unsigned milliseconds;
      std::shared_ptr<AnomalyOrException> anomalyOrException;

      CallResult();
      explicit CallResult(TestPhase testPhase);
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(CallResult) == 24, "sizeof(CallResult) != 24");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(CallResult) == 24, "Debug sizeof(CallResult) != 24");
      #elif NDEBUG
         static_assert(sizeof(CallResult) == 24, "Release sizeof(CallResult) != 24");
      #endif
   #endif

   static_assert(std::is_move_constructible<CallResult>::value, "!std::is_move_constructible<CallResult>::value");
   static_assert(std::is_move_assignable<CallResult>::value, "!std::is_move_assignable<CallResult>::value");
}

template<>
struct ZenUnitEqualizer<ZenUnit::CallResult>
{
   static void AssertEqual(
      const ZenUnit::CallResult& expectedCallResult,
      const ZenUnit::CallResult& actualCallResult);
};
