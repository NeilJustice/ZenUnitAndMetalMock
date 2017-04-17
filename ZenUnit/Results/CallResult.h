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
      long long milliseconds;
      Anomaly anomaly;
      const std::string* exceptionTypeName;
      std::string exceptionWhat;

      CallResult();
      explicit CallResult(TestPhase testPhase);
      virtual ~CallResult() = default;
      virtual void Assign(const CallResult& callResult);
   };

   #ifdef __linux__
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(CallResult) == 312, "Debug sizeof(CallResult) != 312");
      #elif NDEBUG
         static_assert(sizeof(CallResult) == 264, "Release sizeof(CallResult) != 264");
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
