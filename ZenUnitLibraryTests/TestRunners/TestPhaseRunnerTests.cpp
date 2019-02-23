#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestPhaseTranslatorMock.h"
#include "ZenUnitLibraryTests/Tests/Mock/TestMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Function/Mock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(TestPhaseRunnerTests)
   AFACT(Constructor_NewsComponents_SetsGetArgsFunction)
   AFACT(RunTestPhase_FunctionDoesNotThrow_ReturnsNoExceptionThrownTestPhaseResult)
   AFACT(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   FACTS(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndExits0Or1DependingOnArg0Argument)
   AFACT(RunTestPhase_FunctionThrowsZenMockException_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsStdException_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetails_Exits1)
   FACTS(RunTestPhase_TestPhaseResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1);
   EVIDENCE

   TestPhaseRunner _testPhaseRunner;
   ConsoleMock* _consoleMock = nullptr;
   TestPhaseTranslatorMock* _testPhaseTranslatorMock = nullptr;
   StopwatchMock* _stopwatchMock = nullptr;
   VoidTwoArgMemberFunctionCallerMock<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>* _voidTwoArgMemberFunctionCallerMock = nullptr;
   unique_ptr<TestMock> _testMock;
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

   const unsigned _microseconds = ZenUnit::Random<unsigned>();
   const string _testPhaseSuffix = ZenUnit::Random<string>();

   STARTUP
   {
      _testPhaseRunner._console.reset(_consoleMock = new ConsoleMock);
      _testPhaseRunner._testPhaseTranslator.reset(_testPhaseTranslatorMock = new TestPhaseTranslatorMock);
      _testPhaseRunner._stopwatch.reset(_stopwatchMock = new StopwatchMock);
      _testPhaseRunner._voidTwoArgMemberFunctionCaller.reset(
         _voidTwoArgMemberFunctionCallerMock = new VoidTwoArgMemberFunctionCallerMock<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>);
      _testPhaseRunner._call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
      _testMock = make_unique<TestMock>();
   }

   CLEANUP
   {
      TestPhaseRunnerTests::s_numberOfNoThrowCalls = 0;
   }

   TEST(Constructor_NewsComponents_SetsGetArgsFunction)
   {
      TestPhaseRunner testPhaseRunner;
      POINTER_WAS_NEWED(testPhaseRunner._console);
      POINTER_WAS_NEWED(testPhaseRunner._testPhaseTranslator);
      POINTER_WAS_NEWED(testPhaseRunner._stopwatch);
      POINTER_WAS_NEWED(testPhaseRunner._voidTwoArgMemberFunctionCaller);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, testPhaseRunner._call_TestRunner_GetArgs);
   }

   void ExpectStopwatchStartAndStopCalls()
   {
      _stopwatchMock->StartMock.Expect();
      _stopwatchMock->StopMock.Return(_microseconds);
   }

   void AssertStopwatchStartAndStopCalled()
   {
      ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
      ZENMOCK(_stopwatchMock->StopMock.CalledOnce());
   }

   static int s_numberOfNoThrowCalls;
   static void NoThrow(Test* test)
   {
      POINTER_IS_NOT_NULL(test);
      ++s_numberOfNoThrowCalls;
   }

   TEST(RunTestPhase_FunctionDoesNotThrow_ReturnsNoExceptionThrownTestPhaseResult)
   {
      ZenUnitArgs args;
      args.failfast = ZenUnit::Random<bool>();
      GetArgs_ZenMockObject.Return(args);

      ExpectStopwatchStartAndStopCalls();

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(NoThrow, _testMock.get(), TestPhase::Startup);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      ARE_EQUAL(1, TestPhaseRunnerTests::s_numberOfNoThrowCalls);
      AssertStopwatchStartAndStopCalled();

      ZENMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Success, args));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::Startup;
      expectedTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedTestPhaseResult.microseconds = _microseconds;
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowAnomaly(Test* test)
   {
      POINTER_IS_NOT_NULL(test);
      throw Anomaly("NonDefault", "NonDefault", FileLine(), "", "");
   }

   TEST(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   {
      ZenUnitArgs args;
      args.failfast = ZenUnit::Random<bool>();
      GetArgs_ZenMockObject.Return(args);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowAnomaly, _testMock.get(), TestPhase::TestBody);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZENMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Anomaly, args));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::TestBody;
      expectedTestPhaseResult.microseconds = _microseconds;
      Anomaly anomaly("NonDefault", "NonDefault", FileLine(), "", "");
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      expectedTestPhaseResult.testOutcome = TestOutcome::Anomaly;

      ZENMOCK(_consoleMock->WriteColorMock.CalledOnceWith("\n=======\nAnomaly\n=======", Color::Red));
      ZENMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(TestPhase::TestBody));
      ZENMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(anomaly.why));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST1X1(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndExits0Or1DependingOnArg0Argument,
      TestPhase testPhase,
      TestPhase::Constructor,
      TestPhase::Startup,
      TestPhase::Cleanup,
      TestPhase::Destructor)
   {
      ZenUnitArgs args;
      args.failfast = ZenUnit::Random<bool>();
      args.exitZero = ZenUnit::Random<bool>();
      GetArgs_ZenMockObject.Return(args);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowAnomaly, _testMock.get(), testPhase);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();
      ZENMOCK(_consoleMock->WriteColorMock.CalledOnceWith("\n=======\nAnomaly\n=======", Color::Red));
      ZENMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      ZENMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      const Anomaly expectedAnomaly("NonDefault", "NonDefault", FileLine(), "", "");
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedAnomaly.why));
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n===========\nFatal Error\n===========", Color::Red));
      const int expectedExitCode = args.exitZero ? 0 : 1;
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
         "A ZenUnit::Anomaly was thrown from a test class constructor, STARTUP function, or CLEANUP function.\nFail fasting with exit code " +
         std::to_string(expectedExitCode) + ".", expectedExitCode));
      ZENMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Anomaly, args));
   }

   static void ThrowStdException(Test* test)
   {
      POINTER_IS_NOT_NULL(test);
      throw runtime_error("runtime_error_what");
   }

   TEST(RunTestPhase_FunctionThrowsZenMockException_ReturnsExceptionResult)
   {
      ZenUnitArgs args;
      GetArgs_ZenMockObject.Return(args);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());

      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase([](Test*)
      {
         throw ZenMock::UnexpectedCallException("ZenMockedFunctionSignature");
      }, _testMock.get(), testPhase);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZENMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Exception, args));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = testPhase;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<ZenMock::UnexpectedCallException>(),
         ZenMock::UnexpectedCallException::MakeWhat("ZenMockedFunctionSignature").c_str());
      expectedTestPhaseResult.microseconds = _microseconds;

      const string exceptionTypeName = "ZenMock::UnexpectedCallException";
      const size_t expectedEqualsSignsLength =
         exceptionTypeName.size() + strlen(_testPhaseSuffix.c_str());
      const std::string expectedEqualsSigns(expectedEqualsSignsLength, '=');
      const string expectedExceptionNameAndTestPhaseSuffixLines = String::Concat('\n',
         expectedEqualsSigns, '\n',
         exceptionTypeName, _testPhaseSuffix, '\n',
         expectedEqualsSigns);
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
         expectedExceptionNameAndTestPhaseSuffixLines, Color::Red));
      ZENMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      const string expectedWhat = ZenMock::UnexpectedCallException::MakeWhat("ZenMockedFunctionSignature");
      const string expectedTestPhaseSuffixAndWhatLines = String::Concat(
         "what(): \"", expectedWhat, "\"");
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedTestPhaseSuffixAndWhatLines));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST1X1(RunTestPhase_FunctionThrowsStdException_ReturnsExceptionResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ZenUnitArgs args;
      GetArgs_ZenMockObject.Return(args);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowStdException, _testMock.get(), arbitraryTestPhase);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      ZENMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestFailedAndFailFastModeTrue, TestOutcome::Exception, args));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = arbitraryTestPhase;
      expectedTestPhaseResult.microseconds = _microseconds;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException
         = make_shared<AnomalyOrException>(Type::GetName<runtime_error>(), "runtime_error_what");

      ZENMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n==================\nUncaught Exception\n==================", Color::Red));
      ZENMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      ZENMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(TestUtil::NewlineConcat("",
"  Type: std::runtime_error",
"what(): \"runtime_error_what\"")));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowInt(Test*)
   {
      throw 1;
   }

   TEST2X2(RunTestPhase_FunctionThrowsAnIntToTriggerDotDotDotHandler_PrintsFailureDetails_Exits1,
      bool exitZero, int expectedExitCode,
      false, 1,
      true, 0)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.exitZero = exitZero;
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();

      const string testPhaseName = ZenUnit::Random<string>();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.Return(testPhaseName.c_str());
      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowInt, _testMock.get(), testPhase);
      //
      ZENMOCK(GetArgs_ZenMockObject.CalledOnce());
      AssertStopwatchStartAndStopCalled();
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n===========\nFatal Error\n===========", Color::Red));
      ZENMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.CalledOnceWith(testPhase));
      const string expectedExitMessage = String::Concat(
         "Fatal ... exception thrown during test phase: ", testPhaseName, ".\nFail fasting with exit code ", expectedExitCode, ".");
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedExitMessage, expectedExitCode));
      ARE_EQUAL(TestPhaseResult(), testPhaseResult);
   }

   TEST3X3(RunTestPhase_TestPhaseResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1,
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
      const ZenUnitArgs args = [&]()
      {
         ZenUnitArgs args;
         args.failfast = failfast;
         return args;
      }();
      //
      _testPhaseRunner.FailFastIfTestFailedAndFailFastModeTrue(testOutcome, args);
      //
      if (expectFailFast)
      {
         const string expectedFailFastMessage =
            "\n[ZenUnit] A test failed in --fail-fast mode. Exiting with code 1.\n[ZenUnit] Command line: " +
            args.commandLine + " (random seed " + std::to_string(ZenUnitRandomSeed::value) + ")";
         ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedFailFastMessage, 1));
      }
   }

   RUN_TESTS(TestPhaseRunnerTests)

   int TestPhaseRunnerTests::s_numberOfNoThrowCalls;
}
