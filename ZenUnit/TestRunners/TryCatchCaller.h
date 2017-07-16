#pragma once
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Results/CallResult.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"
#include "ZenUnit/Utils/Type.h"

namespace ZenUnit
{
   class Console;
   class Stopwatch;
   class Test;
   class TestPhaseSuffixer;
   struct ZenUnitArgs;

   class TryCatchCaller
   {
      friend class TryCatchCallerTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const TestPhaseSuffixer> _testPhaseSuffixer;
      std::unique_ptr<Stopwatch> _stopwatch;
      std::function<const ZenUnitArgs&()> _TestRunner_GetArgs_ZenMockable;
   public:
      TryCatchCaller();
      virtual ~TryCatchCaller();
      virtual CallResult Call(void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const;
   private:
      template<typename ExceptionType>
      void PopulateCallResultWithExceptionInformation(const ExceptionType& e, CallResult* outCallResult) const
      {
         outCallResult->milliseconds = _stopwatch->Stop();
         const std::string* const exceptionTypeName = Type::GetName(e);
         const char* const what = e.what();
         outCallResult->anomalyOrException = std::make_shared<AnomalyOrException>(exceptionTypeName, what);
         outCallResult->testOutcome = TestOutcome::Exception;
      }
   };
}
