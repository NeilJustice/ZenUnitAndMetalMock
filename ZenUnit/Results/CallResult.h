#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   enum class TestOutcome : unsigned char;
   enum class TestPhase : unsigned char;
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
         static_assert(sizeof(CallResult) == 24);
      #endif
   #elif _MSC_FULL_VER == VS2017Update3 && defined(_WIN64) // VS2017 15.3
      #ifdef _DEBUG
         static_assert(sizeof(CallResult) == 24);
      #elif NDEBUG
         static_assert(sizeof(CallResult) == 24);
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::CallResult>
{
   static void AssertEqual(
      const ZenUnit::CallResult& expectedCallResult,
      const ZenUnit::CallResult& actualCallResult);
};
