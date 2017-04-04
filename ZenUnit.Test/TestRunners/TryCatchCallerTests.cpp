#include "pch.h"
#include "ZenUnit.Test/Console/Mock/ConsoleMock.h"
#include "ZenUnit.Test/Results/Mock/CallResultMock.h"
#include "ZenUnit.Test/Tests/Mock/TestMock.h"
#include "ZenUnit.Test/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/TestRunners/TryCatchCaller.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   TESTS(TryCatchCallerTests)
   SPEC(Constructor_NewsConsoleAndStopwatch_SetsGetArgsFunction)
   SPEC(Call_FunctionDoesNotThrow_ReturnsNoExceptionThrownCallResult)
   SPEC(Call_FunctionThrowsAnomaly_ReturnsAnomalyResult)
   SPEC(Call_FunctionThrowsStdException_ReturnsExceptionResult)
   SPEC(Call_FunctionThrowsStdInvalidArgument_ReturnsExceptionResult)
   SPEC(Call_FunctionThrowsZenMockException_ReturnsExceptionResult)
   SPECX(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetailsImmediately_Exits1)
   SPEC(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_InvalidTestPhase_TriggersAssertion)
   SPECEND

   TryCatchCaller _tryCatchCaller;
   ConsoleMock* _consoleMock;
   StopwatchMock* _stopwatchMock;
   unique_ptr<TestMock> _testMock;
   const unsigned Milliseconds = 1;
   ZENMOCK_NONVOID0_STATIC(ZenUnitArgs, TestRunner, GetArgs)

   STARTUP
   {
      _tryCatchCaller._console.reset(_consoleMock = new ConsoleMock);
      _tryCatchCaller._stopwatch.reset(_stopwatchMock = new StopwatchMock);
      _tryCatchCaller._getArgs = ZENBIND0(GetArgs_ZenMock);
      _testMock = make_unique<TestMock>();
   }

   CLEANUP
   {
      TryCatchCallerTests::numberOfNoThrowCalls = 0;
   }

   TEST(Constructor_NewsConsoleAndStopwatch_SetsGetArgsFunction)
   {
      TryCatchCaller tryCatchCaller;
      WAS_NEWED(tryCatchCaller._console);
      WAS_NEWED(tryCatchCaller._stopwatch);
      FUNCTION_TARGETS(TestRunner::GetArgs, tryCatchCaller._getArgs);
   }

   void ExpectStopwatchStartAndStop()
   {
      _stopwatchMock->StartMock.Expect();
      _stopwatchMock->StopMillisecondsMock.ExpectAndReturn(Milliseconds);
   }

   void AssertStartAndStopCalled()
   {
      ZEN(_stopwatchMock->StartMock.AssertCalledOnce());
      ZEN(_stopwatchMock->StopMillisecondsMock.AssertCalledOnce());
   }

   static int numberOfNoThrowCalls;
   static void NoThrow(Test* test)
   {
      IS_NOT_NULL(test);
      ++numberOfNoThrowCalls;
   }

   TEST(Call_FunctionDoesNotThrow_ReturnsNoExceptionThrownCallResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call(NoThrow, _testMock.get(), TestPhase::Startup);
      //
      ARE_EQUAL(1, TryCatchCallerTests::numberOfNoThrowCalls);
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::Startup;
      expectedCallResult.testOutcome = TestOutcome::Success;
      expectedCallResult.milliseconds = Milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowAnomaly(Test* test)
   {
      IS_NOT_NULL(test);
      throw Anomaly("NonDefault", "NonDefault", FileLine(), "", "");
   }

   TEST(Call_FunctionThrowsAnomaly_ReturnsAnomalyResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call(
         ThrowAnomaly, _testMock.get(), TestPhase::TestBody);
      //
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::TestBody;
      expectedCallResult.testOutcome = TestOutcome::Anomaly;
      expectedCallResult.anomaly = Anomaly("NonDefault", "NonDefault", FileLine(), "", "");
      expectedCallResult.milliseconds = Milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowStdException(Test* test)
   {
      IS_NOT_NULL(test);
      throw runtime_error("what");
   }

   TEST(Call_FunctionThrowsStdException_ReturnsExceptionResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call(
         ThrowStdException, _testMock.get(), TestPhase::TestBody);
      //
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::TestBody;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.exceptionTypeName = Type::GetName<runtime_error>();
      expectedCallResult.exceptionWhat = "what";
      expectedCallResult.milliseconds = Milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowInvalidArgument(Test*)
   {
      throw invalid_argument("what");
   }

   TEST(Call_FunctionThrowsStdInvalidArgument_ReturnsExceptionResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call(
         ThrowInvalidArgument, _testMock.get(), TestPhase::TestBody);
      //
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::TestBody;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.exceptionTypeName = Type::GetName<invalid_argument>();
      expectedCallResult.exceptionWhat = "what";
      expectedCallResult.milliseconds = Milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   TEST(Call_FunctionThrowsZenMockException_ReturnsExceptionResult)
   {
      ExpectStopwatchStartAndStop();
      //
      const CallResult callResult = _tryCatchCaller.Call([](Test*)
      {
         throw ZenMock::FunctionAlreadyExpectedException("ZenMockedFunctionSignature");
      }, _testMock.get(), TestPhase::TestBody);
      //
      AssertStartAndStopCalled();
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::TestBody;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.exceptionTypeName = Type::GetName<ZenMock::FunctionAlreadyExpectedException>();
      expectedCallResult.exceptionWhat =
         ZenMock::FunctionAlreadyExpectedException::MakeWhat("ZenMockedFunctionSignature");
      expectedCallResult.milliseconds = Milliseconds;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   static void ThrowInt(Test*)
   {
      throw 1;
   }

   TEST4X4(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetailsImmediately_Exits1,
      TestPhase testPhase, const string& expectedTestPhaseSuffix, bool exit0, int expectedExitCode,
      TestPhase::Constructor, " in test class constructor", false, 1,
      TestPhase::Constructor, " in test class constructor", true, 0,
      TestPhase::Startup, " in STARTUP", false, 1,
      TestPhase::Startup, " in STARTUP", true, 0,
      TestPhase::TestBody, "", false, 1,
      TestPhase::TestBody, "", true, 0,
      TestPhase::Cleanup, " in CLEANUP", false, 1,
      TestPhase::Cleanup, " in CLEANUP", true, 0)
   {
      ExpectStopwatchStartAndStop();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exit0 = exit0;
      GetArgs_ZenMock.ExpectAndReturn(zenUnitArgs);
      //
      _tryCatchCaller.Call(ThrowInt, _testMock.get(), testPhase);
      //
      AssertStartAndStopCalled();
      ZEN(_consoleMock->WriteLineColorMock.AssertCalledOnceWith("FATALITY!", Color::Red));
      ZEN(GetArgs_ZenMock.AssertCalledOnce());
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(
         String::Concat("Fatal ... exception. Exiting now with exit code 1.",
            expectedTestPhaseSuffix, " (", Milliseconds, " ms)"), expectedExitCode));
   }

   TEST(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_InvalidTestPhase_TriggersAssertion)
   {
      ExpectStopwatchStartAndStop();
      //
      THROWS(_tryCatchCaller.Call(ThrowInt, _testMock.get(), TestPhase::Unset), logic_error,
         R"(assert_true(testPhase == TestPhase::Cleanup) failed in TestPhaseToTestPhaseSuffix()
File.cpp(1))");
      //
      AssertStartAndStopCalled();
   }

   }; RUN(TryCatchCallerTests)

   int TryCatchCallerTests::numberOfNoThrowCalls;
}
