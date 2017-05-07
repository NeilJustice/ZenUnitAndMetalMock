#include "pch.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Results/TestPhaseSuffixer.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Type.h"
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"
#include <memory>

namespace ZenUnit
{
   TryCatchCaller::TryCatchCaller()
      : _console(new Console)
      , _testPhaseSuffixer(new TestPhaseSuffixer)
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
         callResult.anomalyOrException = make_shared<AnomalyOrException>(anomaly);
         callResult.testOutcome = TestOutcome::Anomaly;
         _console->WriteColor("\nAnomaly", Color::Red);
         const char* const testPhaseSuffix = _testPhaseSuffixer->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         _console->WriteLine(anomaly.why);
      }
      catch (const ZenMock::ZenMockException& e)
      {
         PopulateCallResultWithExceptionInformation(e, &callResult);
         _console->WriteColor("\nZenMockException", Color::Red);
         const char* const testPhaseSuffix = _testPhaseSuffixer->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         const string exceptionTypeNameAndWhat = String::Concat(
            "\n  Type: ", *Type::GetName(e), "\nwhat(): \"", e.what(), "\"");
         _console->WriteLine(exceptionTypeNameAndWhat);
      }
      catch (const exception& e)
      {
         PopulateCallResultWithExceptionInformation(e, &callResult);
         _console->WriteColor("\nUncaught Exception", Color::Red);
         const char* const testPhaseSuffix = _testPhaseSuffixer->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         const string exceptionTypeNameAndWhat = String::Concat(
            "\n  Type: ", *Type::GetName(e), '\n',
            "what(): \"", e.what(), "\"");
         _console->WriteLine(exceptionTypeNameAndWhat);
      }
      catch (...)
      {
         const unsigned milliseconds = _stopwatch->Stop();
         const char* const testPhaseSuffix = _testPhaseSuffixer->TestPhaseToTestPhaseSuffix(testPhase);
         _console->WriteLineColor("FATALITY", Color::Red);
         const string exitLine = String::Concat(
            "Fatal ... exception. Fail fasting with exit code 1 unless -exit0 specified.",
            testPhaseSuffix, " (", milliseconds, " ms)");
         const ZenUnitArgs zenUnitArgs = _getArgs();
         _console->WriteLineAndExit(exitLine, zenUnitArgs.exit0 ? 0 : 1);
      }
      return callResult;
   }
}
