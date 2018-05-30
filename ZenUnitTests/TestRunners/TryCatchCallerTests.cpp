#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestPhaseSuffixerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

namespace ZenUnit
{
   TESTS(TryCatchCallerTests)
   AFACT(Constructor_NewsComponents_SetsGetArgsFunction)
   AFACT(Call_FunctionDoesNotThrow_ReturnsNoExceptionThrownCallResult)
   FACTS(Call_FunctionThrowsAnomaly_ReturnsAnomalyResult)
   AFACT(Call_FunctionThrowsZenMockException_ReturnsExceptionResult)
   FACTS(Call_FunctionThrowsStdException_ReturnsExceptionResult)
   FACTS(Call_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetails_Exits1)
   FACTS(Call_CallResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1);
   EVIDENCE

   TryCatchCaller _tryCatchCaller;
   ConsoleMock* _consoleMock = nullptr;
   TestPhaseSuffixerMock* _testPhaseSuffixerMock = nullptr;
   StopwatchMock* _stopwatchMock = nullptr;
   VoidTwoArgMemberFunctionCallerMock<TryCatchCaller, TestOutcome, bool>* _voidTwoArgMemberFunctionCallerMock = nullptr;
   unique_ptr<TestMock> _testMock;
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

   const unsigned _microseconds = ZenUnit::Random<unsigned>();
   const string _testPhaseSuffix = ZenUnit::Random<string>();

   STARTUP
   {
      _tryCatchCaller._console.reset(_consoleMock = new ConsoleMock);
      _tryCatchCaller._testPhaseSuffixer.reset(_testPhaseSuffixerMock = new TestPhaseSuffixerMock);
      _tryCatchCaller._stopwatch.reset(_stopwatchMock = new StopwatchMock);
      _tryCatchCaller._voidTwoArgMemberFunctionCaller.reset(
         _voidTwoArgMemberFunctionCallerMock = new VoidTwoArgMemberFunctionCallerMock<TryCatchCaller, TestOutcome, bool>);
      _tryCatchCaller.call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
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
      POINTER_WAS_NEWED(tryCatchCaller._voidTwoArgMemberFunctionCaller);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, tryCatchCaller.call_TestRunner_GetArgs);
   }

   void ExpectStopwatchStartAndStopCalls()
   {
      _stopwatchMock->StartMock.Expect();
      _stopwatchMock->StopMock.Return(_microseconds);
   }

   void AssertStopwatchStartAndStopCalled()
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
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failfast = ZenUnit::Random<bool>();
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      ExpectStopwatchStartAndStopCalls();

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();
      //
      const CallResult callResult = _tryCatchCaller.Call(NoThrow, _testMock.get(), TestPhase::Startup);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      ARE_EQUAL(1, TryCatchCallerTests::s_numberOfNoThrowCalls);
      AssertStopwatchStartAndStopCalled();

      ZEN(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_tryCatchCaller, &TryCatchCaller::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Success, zenUnitArgs.failfast));

      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::Startup;
      expectedCallResult.testOutcome = TestOutcome::Success;
      expectedCallResult.microseconds = _microseconds;
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
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failfast = ZenUnit::Random<bool>();
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const CallResult callResult = _tryCatchCaller.Call(ThrowAnomaly, _testMock.get(), arbitraryTestPhase);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZEN(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_tryCatchCaller, &TryCatchCaller::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Anomaly, zenUnitArgs.failfast));

      CallResult expectedCallResult;
      expectedCallResult.testPhase = arbitraryTestPhase;
      expectedCallResult.microseconds = _microseconds;
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

   TEST(Call_FunctionThrowsZenMockException_ReturnsExceptionResult)
   {
      ZenUnitArgs zenUnitArgs;
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());

      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);
      //
      const CallResult callResult = _tryCatchCaller.Call([](Test*)
      {
         throw ZenMock::UnexpectedCallException("ZenMockedFunctionSignature");
      }, _testMock.get(), testPhase);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZEN(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_tryCatchCaller, &TryCatchCaller::FailFastIfTestFailedAndFailFastModeTrue,
         TestOutcome::Exception, zenUnitArgs.failfast));

      CallResult expectedCallResult;
      expectedCallResult.testPhase = testPhase;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<ZenMock::UnexpectedCallException>(),
         ZenMock::UnexpectedCallException::MakeWhat("ZenMockedFunctionSignature").c_str());
      expectedCallResult.microseconds = _microseconds;

      const string exceptionTypeName = "ZenMock::UnexpectedCallException";
      const size_t expectedEqualsSignsLength =
         exceptionTypeName.size() + strlen(_testPhaseSuffix.c_str());
      const std::string expectedEqualsSigns(expectedEqualsSignsLength, '=');
      const string expectedExceptionNameAndTestPhaseSuffixLines = String::Concat('\n',
         expectedEqualsSigns, '\n',
         exceptionTypeName, _testPhaseSuffix, '\n',
         expectedEqualsSigns);
      ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith(
         expectedExceptionNameAndTestPhaseSuffixLines, Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      const string expectedWhat = ZenMock::UnexpectedCallException::MakeWhat("ZenMockedFunctionSignature");
      const string expectedTestPhaseSuffixAndWhatLines = String::Concat(
         "what(): \"", expectedWhat, "\"");
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedTestPhaseSuffixAndWhatLines));
      ARE_EQUAL(expectedCallResult, callResult);
   }

   TEST1X1(Call_FunctionThrowsStdException_ReturnsExceptionResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ZenUnitArgs zenUnitArgs;
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const CallResult callResult = _tryCatchCaller.Call(ThrowStdException, _testMock.get(), arbitraryTestPhase);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZEN(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_tryCatchCaller, &TryCatchCaller::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Exception, zenUnitArgs.failfast));

      CallResult expectedCallResult;
      expectedCallResult.testPhase = arbitraryTestPhase;
      expectedCallResult.microseconds = _microseconds;
      expectedCallResult.testOutcome = TestOutcome::Exception;
      expectedCallResult.anomalyOrException
         = make_shared<AnomalyOrException>(Type::GetName<runtime_error>(), "runtime_error_what");

      ZEN(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n=========\nException\n=========", Color::Red));
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
      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      _testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exit0 = exit0;
      GetArgs_ZenMockObject.Return(zenUnitArgs);
      //
      const CallResult callResult = _tryCatchCaller.Call(ThrowInt, _testMock.get(), arbitraryTestPhase);
      //
      AssertStopwatchStartAndStopCalled();

      ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith("FATALITY", Color::Red));
      ZEN(_testPhaseSuffixerMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
         String::Concat("Fatal ... exception. ", expectedExitMessage,
            _testPhaseSuffix.c_str(), " ", _microseconds, "us"), expectedExitCode));
      ARE_EQUAL(CallResult(), callResult);
   }

   TEST3X3(Call_CallResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1,
      TestOutcome testOutcome, bool failfast, bool expectFailFast,
      TestOutcome::Unset, false, false,
      TestOutcome::Success, false, false,
      TestOutcome::Anomaly, false, false,
      TestOutcome::SuccessButPastDeadline, false, false,
      TestOutcome::Exception, false, false,
      TestOutcome::Unset, true, true,
      TestOutcome::Success, true, false,
      TestOutcome::Anomaly, true, true,
      TestOutcome::SuccessButPastDeadline, true, true,
      TestOutcome::Exception, true, true)
   {
      if (expectFailFast)
      {
         _consoleMock->WriteLineAndExitMock.Expect();
      }
      //
      _tryCatchCaller.FailFastIfTestFailedAndFailFastModeTrue(testOutcome, failfast);
      //
      if (expectFailFast)
      {
         ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
            "\nZenUnit> -failfast exiting with code 1.", 1));
      }
   }

   RUN_TESTS(TryCatchCallerTests)

   int TryCatchCallerTests::s_numberOfNoThrowCalls;
}
