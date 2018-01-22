#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestPhaseSuffixerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

namespace ZenUnit
{
   TESTS(TryCatchCallerTests)
   AFACT(Constructor_NewsComponents_SetsGetArgsFunction)
   AFACT(Call_FunctionDoesNotThrow_ReturnsNoExceptionThrownCallResult)
   FACTS(Call_FunctionThrowsAnomaly_ReturnsAnomalyResult)
   FACTS(Call_FunctionThrowsZenMockException_ReturnsExceptionResult)
   FACTS(Call_FunctionThrowsStdException_ReturnsExceptionResult)
   FACTS(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetails_Exits1)
   EVIDENCE

   TryCatchCaller _tryCatchCaller;
   ConsoleMock* _consoleMock;
   TestPhaseSuffixerMock* _testPhaseSuffixerMock;
   StopwatchMock* _stopwatchMock;
   unique_ptr<TestMock> _testMock;
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

   const unsigned _milliseconds = Random<unsigned>();
   const string _testPhaseSuffix = Random<string>();

   STARTUP
   {
      _tryCatchCaller._console.reset(_consoleMock = new ConsoleMock);
      _tryCatchCaller._testPhaseSuffixer.reset(_testPhaseSuffixerMock = new TestPhaseSuffixerMock);
      _tryCatchCaller._stopwatch.reset(_stopwatchMock = new StopwatchMock);
      _tryCatchCaller.call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
      _testMock = make_unique<TestMock>();
   }

   CLEANUP
   {
      TryCatchCallerTests::s_numberOfNoThrowCalls = 0;
   }

   TEST(Constructor_NewsComponents_SetsGetArgsFunction)
   {
      TryCatchCaller tryCatchCaller;
      POINTER_WAS_NEWED(tryCatchCaller._console);
      POINTER_WAS_NEWED(tryCatchCaller._testPhaseSuffixer);
      POINTER_WAS_NEWED(tryCatchCaller._stopwatch);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, tryCatchCaller.call_TestRunner_GetArgs);
   }

   void ExpectStopwatchStartAndStop()
   {
      _stopwatchMock->StartMock.Expect();
      _stopwatchMock->StopMock.Return(_milliseconds);
   }

   void AssertStartAndStopCalled()
   {
      ZEN(_stopwatchMock->StartMock.CalledOnce());
      ZEN(_stopwatchMock->StopMock.CalledOnce());
   }

   static int s_numberOfNoThrowCalls;
   static void NoThrow(Test* test)
   {
      IS_NOT_NULL(test);
      ++s_numberOfNoThrowCalls;
   }

   TEST(Call_FunctionDoesNotThrow_ReturnsNoExceptionThrownCallResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call(NoThrow, _testMock.get(), TestPhase::Startup);
      //
      ARE_EQUAL(1, TryCatchCallerTests::s_numberOfNoThrowCalls);
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::Startup;
      expectedCallResult.testOutcome = TestOutcome::Success;
      expectedCallResult.milliseconds = _milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowAnomaly(Test* test)
   {
      IS_NOT_NULL(test);
      throw Anomaly("NonDefault", "NonDefault", FileLine(), "", "");
   }

   TEST1X1(Call_FunctionThrowsAnomaly_ReturnsAnomalyResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ExpectStopwatchStartAndStop();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const CallResult callResult = _tryCatchCaller.Call(ThrowAnomaly, _testMock.get(), arbitraryTestPhase);
      //
      AssertStartAndStopCalled();

      CallResult expectedCallResult;
      expectedCallResult.testPhase = arbitraryTestPhase;
      expectedCallResult.milliseconds = _milliseconds;
      Anomaly anomaly("NonDefault", "NonDefault", FileLine(), "", "");
      expectedCallResult.anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      expectedCallResult.testOutcome = TestOutcome::Anomaly;

      ZEN(_consoleMock->WriteColorMock.CalledOnceWith("\n=======\nAnomaly\n=======", Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZEN(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(anomaly.why));
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowStdException(Test* test)
   {
      IS_NOT_NULL(test);
      throw runtime_error("runtime_error_what");
   }

   TEST1X1(Call_FunctionThrowsZenMockException_ReturnsExceptionResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ExpectStopwatchStartAndStop();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const CallResult callResult = _tryCatchCaller.Call([](Test*)
      {
         throw ZenMock::FunctionAlreadyExpectedException("ZenMockedFunctionSignature");
      }, _testMock.get(), arbitraryTestPhase);
      //
      AssertStartAndStopCalled();

      CallResult expectedCallResult;
      expectedCallResult.testPhase = arbitraryTestPhase;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<ZenMock::FunctionAlreadyExpectedException>(),
         ZenMock::FunctionAlreadyExpectedException::MakeWhat("ZenMockedFunctionSignature").c_str());
      expectedCallResult.milliseconds = _milliseconds;

      ZEN(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n=========================\nUncaught ZenMockException\n=========================", Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZEN(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(R"(
  Type: ZenMock::FunctionAlreadyExpectedException
what(): "For ZenMocked function "ZenMockedFunctionSignature":
Already called [FunctionName]Mock.[Expect|Return|ReturnValues|Throw]().")"));
      ARE_EQUAL(expectedCallResult, callResult);
   }

   TEST1X1(Call_FunctionThrowsStdException_ReturnsExceptionResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ExpectStopwatchStartAndStop();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const CallResult callResult = _tryCatchCaller.Call(ThrowStdException, _testMock.get(), arbitraryTestPhase);
      //
      AssertStartAndStopCalled();

      CallResult expectedCallResult;
      expectedCallResult.testPhase = arbitraryTestPhase;
      expectedCallResult.milliseconds = _milliseconds;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.anomalyOrException
         = make_shared<AnomalyOrException>(Type::GetName<runtime_error>(), "runtime_error_what");

      ZEN(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n==================\nUncaught Exception\n==================", Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZEN(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(R"(
  Type: std::runtime_error
what(): "runtime_error_what")"));
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowInt(Test*)
   {
      throw 1;
   }

   TEST4X4(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetails_Exits1,
      TestPhase arbitraryTestPhase, bool exit0, int expectedExitCode, const char* expectedExitMessage,
      TestPhase::Constructor, false, 1, "Exiting with code 1.",
      TestPhase::Constructor, true, 0, "Exiting with code 0 due to -exit0 being specified.",
      TestPhase::TestBody, false, 1, "Exiting with code 1.",
      TestPhase::TestBody, true, 0, "Exiting with code 0 due to -exit0 being specified.")
   {
      ExpectStopwatchStartAndStop();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exit0 = exit0;
      GetArgs_ZenMock.Return(zenUnitArgs);
      //
      _tryCatchCaller.Call(ThrowInt, _testMock.get(), arbitraryTestPhase);
      //
      AssertStartAndStopCalled();
      ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith("FATALITY", Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZEN(GetArgs_ZenMock.CalledOnce());
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
         String::Concat("Fatal ... exception. ", expectedExitMessage,
            _testPhaseSuffix.c_str(), " (", _milliseconds, " ms)"), expectedExitCode));
   }

   }; RUN_TESTS(TryCatchCallerTests)

   int TryCatchCallerTests::s_numberOfNoThrowCalls;
}
