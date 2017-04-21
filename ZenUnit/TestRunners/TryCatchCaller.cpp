#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenUnit
{
   TryCatchCaller::TryCatchCaller()
      : _console(new Console)
      , _stopwatch(new Stopwatch)
      , _getArgs(TestRunner::GetArgs)
   {
   }

   TryCatchCaller::~TryCatchCaller() = default;

   CallResult TryCatchCaller::Call(
      void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const
   {
      CallResult callResult(testPhase);
      _stopwatch->Start();
      try
      {
         testPhaseFunction(test);
         callResult.milliseconds = _stopwatch->Stop();
      }
      catch (const Anomaly& anomaly)
      {
         callResult.milliseconds = _stopwatch->Stop();
         callResult.anomaly = make_shared<Anomaly>(anomaly);
         callResult.testOutcome = TestOutcome::Anomaly;
      }
      catch (const ZenMock::ZenMockException& e)
      {
         PopulateCallResult(e, &callResult);
      }
      catch (const exception& e)
      {
         PopulateCallResult(e, &callResult);
      }
      catch (...)
      {
         const unsigned milliseconds = _stopwatch->Stop();
         const string testPhaseSuffix = TestPhaseToTestPhaseSuffix(testPhase);
         _console->WriteLineColor("FATALITY!", Color::Red);
         const string exitLine = String::Concat(
            "Fatal ... exception. Exiting now with exit code 1.",
            testPhaseSuffix, " (", milliseconds, " ms)");
         const ZenUnitArgs zenUnitArgs = _getArgs();
         _console->WriteLineAndExit(exitLine, zenUnitArgs.exit0 ? 0 : 1);
      }
      return callResult;
   }
}
