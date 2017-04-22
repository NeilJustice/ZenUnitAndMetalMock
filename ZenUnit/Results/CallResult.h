#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct CallResult
   {
      TestPhase testPhase;
      TestOutcome testOutcome;
      unsigned milliseconds;
      std::shared_ptr<Anomaly> anomaly;
      const std::string* exceptionTypeName;
      std::shared_ptr<std::string> exceptionWhat;

      CallResult();
      explicit CallResult(TestPhase testPhase);
      virtual ~CallResult() = default;
      virtual void Assign(const CallResult& callResult);
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(CallResult) == 56, "sizeof(CallResult) != 56");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(CallResult) == 56, "Debug sizeof(CallResult) != 56");
      #elif NDEBUG
         static_assert(sizeof(CallResult) == 56, "Release sizeof(CallResult) != 56");
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
