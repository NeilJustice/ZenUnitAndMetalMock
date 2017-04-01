#pragma once
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Anomaly/Anomaly.h"
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
}

template<>
struct ZenUnitEqualizer<ZenUnit::CallResult>
{
   static void AssertEqual(
      const ZenUnit::CallResult& expectedCallResult,
      const ZenUnit::CallResult& actualCallResult);
};
