#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestPhaseTranslatorMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizer.h"
#include "ZenUnitTestUtils/TestUtil.h"

namespace ZenUnit
{
   TESTS(TestPhaseRunnerTests)
   AFACT(Constructor_NewsComponents_SetsGetArgsFunction)
   AFACT(RunTestPhase_FunctionDoesNotThrow_ReturnsNoExceptionThrownTestPhaseResult)
   AFACT(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   FACTS(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndExits0Or1DependingOnArg0Argument)
   AFACT(RunTestPhase_FunctionThrowsMetalMockException_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsStdException_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsAnIntToTriggerDotDotDotExceptionHandler_PrintsFailureDetails_Exits1)
   FACTS(RunTestPhase_TestPhaseResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1);
   EVIDENCE

   TestPhaseRunner _testPhaseRunner;
   ConsoleMock* _consoleMock = nullptr;
   TestPhaseTranslatorMock* _testPhaseTranslatorMock = nullptr;
   // Function Callers
   VoidTwoArgMemberFunctionCallerMock<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>* _voidTwoArgMemberFunctionCallerMock = nullptr;
   WatchMock* _watchMock = nullptr;
   METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)
   // Mutables
   StopwatchMock* _testPhaseStopwatchMock = nullptr;
   // Testing
   unique_ptr<TestMock> _testMock;
   const unsigned _microseconds = ZenUnit::Random<unsigned>();
   const string _testPhaseSuffix = ZenUnit::Random<string>();

   STARTUP
   {
      _testPhaseRunner._console.reset(_consoleMock = new ConsoleMock);
      _testPhaseRunner._testPhaseTranslator.reset(_testPhaseTranslatorMock = new TestPhaseTranslatorMock);
      _testPhaseRunner._watch.reset(_watchMock = new WatchMock);
      // Function Callers
      _testPhaseRunner._voidTwoArgMemberFunctionCaller.reset(_voidTwoArgMemberFunctionCallerMock = new VoidTwoArgMemberFunctionCallerMock<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>);
      _testPhaseRunner._call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(GetZenUnitArgsMock);
      // Mutables
      _testPhaseRunner._testPhaseStopwatch.reset(_testPhaseStopwatchMock = new StopwatchMock);
      // Testing
      _testMock = make_unique<TestMock>();
   }

   CLEANUP
   {
      TestPhaseRunnerTests::s_numberOfNoThrowCalls = 0;
   }

   TEST(Constructor_NewsComponents_SetsGetArgsFunction)
   {
      TestPhaseRunner testPhaseRunner;
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._console);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._testPhaseTranslator);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._voidTwoArgMemberFunctionCaller);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._watch);
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, testPhaseRunner._call_ZenUnitTestRunner_GetZenUnitArgs);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._testPhaseStopwatch);
   }

   void ExpectStopwatchStartAndStopCalls()
   {
      _testPhaseStopwatchMock->StartMock.Expect();
      _testPhaseStopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.Return(_microseconds);
   }

   void AssertStopwatchStartAndStopCalled()
   {
      METALMOCK(_testPhaseStopwatchMock->StartMock.CalledOnce());
      METALMOCK(_testPhaseStopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.CalledOnce());
   }

   static int s_numberOfNoThrowCalls;
   static void NoThrow(Test* test)
   {
      IS_NOT_NULLPTR(test);
      ++s_numberOfNoThrowCalls;
   }

   TEST(RunTestPhase_FunctionDoesNotThrow_ReturnsNoExceptionThrownTestPhaseResult)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failFast = ZenUnit::Random<bool>();
      GetZenUnitArgsMock.Return(zenUnitArgs);

      ExpectStopwatchStartAndStopCalls();

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(NoThrow, _testMock.get(), TestPhase::Startup);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      ARE_EQUAL(1, TestPhaseRunnerTests::s_numberOfNoThrowCalls);
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue, TestOutcome::Success, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::Startup;
      expectedTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedTestPhaseResult.microseconds = _microseconds;
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowAnomaly(Test* test)
   {
      IS_NOT_NULLPTR(test);
      throw Anomaly("NonDefault", "NonDefault", FileLine(), "", "");
   }

   TEST(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failFast = ZenUnit::Random<bool>();
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowAnomaly, _testMock.get(), TestPhase::TestBody);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue, TestOutcome::Anomaly, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::TestBody;
      expectedTestPhaseResult.microseconds = _microseconds;
      Anomaly anomaly("NonDefault", "NonDefault", FileLine(), "", "");
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      expectedTestPhaseResult.testOutcome = TestOutcome::Anomaly;

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith("\n================\nFailed Assertion\n================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(TestPhase::TestBody));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(anomaly.why));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST1X1(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndExits0Or1DependingOnArg0Argument,
      TestPhase testPhase,
      TestPhase::Constructor,
      TestPhase::Startup,
      TestPhase::Cleanup,
      TestPhase::Destructor)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failFast = ZenUnit::Random<bool>();
      zenUnitArgs.alwaysExit0 = ZenUnit::Random<bool>();
      GetZenUnitArgsMock.Return(zenUnitArgs);

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
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();
      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith("\n================\nFailed Assertion\n================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      const Anomaly expectedAnomaly("NonDefault", "NonDefault", FileLine(), "", "");
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedAnomaly.why));
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n===========\nFatal Error\n===========", Color::Red));
      const int expectedExitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
         "A ZenUnit::Anomaly was thrown from a test class constructor, STARTUP function, or CLEANUP function.\nFail fasting with exit code " +
         std::to_string(expectedExitCode) + ".", expectedExitCode));
      METALMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue, TestOutcome::Anomaly, zenUnitArgs));
   }

   static void ThrowStdException(Test* test)
   {
      IS_NOT_NULLPTR(test);
      throw runtime_error("runtime_error_what");
   }

   TEST(RunTestPhase_FunctionThrowsMetalMockException_ReturnsExceptionResult)
   {
      ZenUnitArgs zenUnitArgs;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());

      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase([](Test*)
      {
         throw MetalMock::UnexpectedCallException("MetalMockedFunctionSignature");
      }, _testMock.get(), testPhase);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue, TestOutcome::Exception, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = testPhase;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<MetalMock::UnexpectedCallException>(),
         MetalMock::UnexpectedCallException::MakeWhat("MetalMockedFunctionSignature").c_str());
      expectedTestPhaseResult.microseconds = _microseconds;

      const string exceptionTypeName = "MetalMock::UnexpectedCallException";
      const size_t expectedEqualsSignsLength =
         exceptionTypeName.size() + strlen(_testPhaseSuffix.c_str());
      const std::string expectedEqualsSigns(expectedEqualsSignsLength, '=');
      const string expectedExceptionNameAndTestPhaseSuffixLines = String::Concat('\n',
         expectedEqualsSigns, '\n',
         exceptionTypeName, _testPhaseSuffix, '\n',
         expectedEqualsSigns);
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
         expectedExceptionNameAndTestPhaseSuffixLines, Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      const string expectedWhat = MetalMock::UnexpectedCallException::MakeWhat("MetalMockedFunctionSignature");
      const string expectedTestPhaseSuffixAndWhatLines = String::Concat(
         "what(): \"", expectedWhat, "\"");
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedTestPhaseSuffixAndWhatLines));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST1X1(RunTestPhase_FunctionThrowsStdException_ReturnsExceptionResult,
      TestPhase arbitraryTestPhase,
      TestPhase::Startup,
      TestPhase::TestBody)
   {
      ZenUnitArgs zenUnitArgs;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _voidTwoArgMemberFunctionCallerMock->ConstCallMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowStdException, _testMock.get(), arbitraryTestPhase);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_voidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue, TestOutcome::Exception, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = arbitraryTestPhase;
      expectedTestPhaseResult.microseconds = _microseconds;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException
         = make_shared<AnomalyOrException>(Type::GetName<runtime_error>(), "runtime_error_what");

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n==================\nUncaught Exception\n==================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(arbitraryTestPhase));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(TestUtil::NewlineConcat("",
"  Type: std::runtime_error",
"what(): \"runtime_error_what\"")));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowInt(Test*)
   {
      throw 1;
   }

   TEST2X2(RunTestPhase_FunctionThrowsAnIntToTriggerDotDotDotExceptionHandler_PrintsFailureDetails_Exits1,
      bool alwaysExit0, int expectedExitCode,
      false, 1,
      true, 0)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _testPhaseStopwatchMock->StartMock.Expect();

      const string testRunDurationInSeconds = _testPhaseStopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

      _consoleMock->WriteLineColorMock.Expect();

      _consoleMock->WriteColorMock.Expect();

      const string endTime = _watchMock->DateTimeNowMock.ReturnRandom();

      _consoleMock->WriteLineMock.Expect();

      const string testPhaseName = ZenUnit::Random<string>();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.Return(testPhaseName.c_str());

      _consoleMock->WriteLineAndExitMock.Expect();

      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowInt, _testMock.get(), testPhase);
      //
      METALMOCK(_testPhaseStopwatchMock->StartMock.CalledOnce());
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      METALMOCK(_testPhaseStopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n==========================\nFatal ... Exception Thrown\n==========================\n", Color::Red));
      METALMOCK(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { ">>------> ", Color::Red },
         { ">>------> ", Color::Red },
         { ">>------> ", Color::Red },
         { ">>------> ", Color::Red },
         { ">>------> ", Color::Red },
         { ">>------> ", Color::Red },
         { ">>-FAIL-> ", Color::Red }
      }));
      METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { " Completed: " + zenUnitArgs.commandLine },
         { " StartTime: " + zenUnitArgs.startDateTime },
         { "   EndTime: " + endTime },
         { "  Duration: " + testRunDurationInSeconds + " seconds" },
         { "RandomSeed: --random-seed=" + to_string(zenUnitArgs.randomSeed) },
         { "    Result: Fatal ... exception thrown during test phase: " + testPhaseName }
      }));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.CalledOnceWith(testPhase));
      const string expectedExitCodeLine = "  ExitCode: " + to_string(expectedExitCode);
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedExitCodeLine, expectedExitCode));
   }

   TEST3X3(RunTestPhase_TestPhaseResultIsNotSuccessAndFailFastIsTrue_WritesFailFastMessageAndExits1,
      TestOutcome testOutcome, bool failFast, bool expectFailFast,
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
         args.failFast = failFast;
         return args;
      }();
      //
      _testPhaseRunner.FailFastIfTestOutcomeIsNotSuccessAndFailFastModeIsTrue(testOutcome, args);
      //
      if (expectFailFast)
      {
         const string expectedFailFastMessage = String::Concat(
            "\n[ZenUnit] A test failed in --fail-fast mode. Exiting with code 1.\n[ZenUnit] Command line: ",
            args.commandLine, " (--random-seed=", ZenUnitRandomSeed::value, ')');
         METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedFailFastMessage, 1));
      }
   }

   RUN_TESTS(TestPhaseRunnerTests)

   int TestPhaseRunnerTests::s_numberOfNoThrowCalls;
}
