#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestRunStopwatchStopperMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestPhaseTranslatorMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestPhaseRunnerTests)
   AFACT(DefaultConstructor_NewsComponents_SetsGetArgsFunction)
   AFACT(RunTestPhase_FunctionDoesNotThrowException_ReturnsNoExceptionThrownTestPhaseResult)
   AFACT(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   FACTS(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndFailFastExitsWithCode1UnlessAlwaysExit0IsTrue)
   AFACT(RunTestPhase_FunctionThrowsStdException_TestPhaseIsTestBody_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsStdException_TestPhaseIsNotTestBody_WritesErrorMessageAndFailFastExitsWithCode1UnlessAlwaysExit0IsTrue)
   AFACT(RunTestPhase_FunctionThrowsMetalMockException_ReturnsExceptionResult)
   FACTS(RunTestPhase_FunctionThrowsAnIntToTriggerDotDotDotExceptionHandler_PrintsFailureDetails_Exits1)
   AFACT(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsFalse_DoesNothing)
   AFACT(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsTrue_TestOutcomeIsSuccess_DoesNothing)
   FACTS(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsTrue_TestPhaseResultIsNotSuccess_WritesFailFastMessage_ExitsWithCode1UnlessAlwaysExit0IsTrue);
   EVIDENCE

   TestPhaseRunner _testPhaseRunner;
   // Function Pointers
   METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)
   // Function Callers
   VoidTwoArgMemberFunctionCallerMock<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>*
      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock = nullptr;
   // Constant Components
   ConsoleMock* _consoleMock = nullptr;
   TestPhaseTranslatorMock* _testPhaseTranslatorMock = nullptr;
   WatchMock* _watchMock = nullptr;
   // Mutable Components
   StopwatchMock* _testPhaseStopwatchMock = nullptr;
   TestRunStopwatchStopperMock* _testRunStopwatchStopperMock = nullptr;
   // Test-Only Component
   unique_ptr<TestMock> _testMock;

   const unsigned _elapsedMicroseconds = ZenUnit::Random<unsigned>();
   const string _testPhaseSuffix = ZenUnit::Random<string>();

   static int s_numberOfCallsToFunctionThatDoesNotThrowAnException;
   static string s_stdExceptionMessage;
   static Anomaly s_anomaly;

   STARTUP
   {
      // Function Pointers
      _testPhaseRunner._call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(GetZenUnitArgsMock);
      // Function Callers
      _testPhaseRunner._caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess.reset(
         _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock = new VoidTwoArgMemberFunctionCallerMock<
         TestPhaseRunner, TestOutcome, const ZenUnitArgs&>);
      // Constant Components
      _testPhaseRunner._console.reset(_consoleMock = new ConsoleMock);
      _testPhaseRunner._testPhaseTranslator.reset(_testPhaseTranslatorMock = new TestPhaseTranslatorMock);
      _testPhaseRunner._testRunStopwatchStopper.reset(_testRunStopwatchStopperMock = new TestRunStopwatchStopperMock);
      _testPhaseRunner._watch.reset(_watchMock = new WatchMock);
      // Mutable Component
      _testPhaseRunner._testPhaseStopwatch.reset(_testPhaseStopwatchMock = new StopwatchMock);
      // Test-Only Component
      _testMock = make_unique<TestMock>();

      s_stdExceptionMessage = ZenUnit::Random<string>();
      s_anomaly = Anomaly(ZenUnit::Random<string>(), ZenUnit::Random<string>(), FilePathLineNumber(), "", "");
   }

   CLEANUP
   {
      TestPhaseRunnerTests::s_numberOfCallsToFunctionThatDoesNotThrowAnException = 0;
   }

   TEST(DefaultConstructor_NewsComponents_SetsGetArgsFunction)
   {
      TestPhaseRunner testPhaseRunner;
      // Function Callers
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, testPhaseRunner._call_ZenUnitTestRunner_GetZenUnitArgs);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._console);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._testPhaseTranslator);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._testRunStopwatchStopper);
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._watch);
      // Mutable Components
      DELETE_TO_ASSERT_NEWED(testPhaseRunner._testPhaseStopwatch);
   }

   void ExpectStopwatchStartAndStopCalls()
   {
      _testPhaseStopwatchMock->StartMock.Expect();
      _testPhaseStopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.Return(_elapsedMicroseconds);
   }

   void AssertStopwatchStartAndStopCalled()
   {
      METALMOCK(_testPhaseStopwatchMock->StartMock.CalledOnce());
      METALMOCK(_testPhaseStopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.CalledOnce());
   }

   static void FunctionThatDoesNotThrowAnException(Test* test)
   {
      IS_NOT_NULLPTR(test);
      ++s_numberOfCallsToFunctionThatDoesNotThrowAnException;
   }

   TEST(RunTestPhase_FunctionDoesNotThrowException_ReturnsNoExceptionThrownTestPhaseResult)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.failFast = ZenUnit::Random<bool>();
      GetZenUnitArgsMock.Return(zenUnitArgs);

      ExpectStopwatchStartAndStopCalls();

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(
         FunctionThatDoesNotThrowAnException, _testMock.get(), TestPhase::Startup);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      ARE_EQUAL(1, TestPhaseRunnerTests::s_numberOfCallsToFunctionThatDoesNotThrowAnException);
      AssertStopwatchStartAndStopCalled();
      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Success, zenUnitArgs));
      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::Startup;
      expectedTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowAnomaly(Test* test)
   {
      IS_NOT_NULLPTR(test);
      throw s_anomaly;
   }

   TEST(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsTestBody_ReturnsAnomalyResult)
   {
      const ZenUnitArgs zenUnitArgs = GetZenUnitArgsMock.ReturnRandom();

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();

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

      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Anomaly, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::TestBody;
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(s_anomaly);
      expectedTestPhaseResult.testOutcome = TestOutcome::Anomaly;

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n================\nFailed Assertion\n================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(TestPhase::TestBody));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(s_anomaly.why));
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST3X3(RunTestPhase_FunctionThrowsAnomaly_TestPhaseIsNotTestBody_WritesErrorMessageAndFailFastExitsWithCode1UnlessAlwaysExit0IsTrue,
      TestPhase testPhase, bool alwaysExit0, int expectedExitCode,
      TestPhase::Constructor, false, 1,
      TestPhase::Startup, false, 1,
      TestPhase::Cleanup, false, 1,
      TestPhase::Destructor, false, 1,
      TestPhase::Constructor, true, 0,
      TestPhase::Startup, true, 0,
      TestPhase::Cleanup, true, 0,
      TestPhase::Destructor, true, 0)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();

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

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n================\nFailed Assertion\n================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(s_anomaly.why));

      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n===========\nFatal Error\n===========", Color::Red));
      const string expectedExitMessage = String::ConcatValues(
         "[ZenUnit] TestResult: A ZenUnit::Anomaly was thrown from a test class constructor, STARTUP function, or CLEANUP function.\n",
         "[ZenUnit]   ExitCode: ", expectedExitCode);
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedExitMessage, expectedExitCode));

      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Anomaly, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = testPhase;
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
      expectedTestPhaseResult.testOutcome = TestOutcome::Anomaly;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(s_anomaly);
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST(RunTestPhase_FunctionThrowsStdException_TestPhaseIsTestBody_ReturnsExceptionResult)
   {
      const ZenUnitArgs zenUnitArgs = GetZenUnitArgsMock.ReturnRandom();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();

      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowStdException, _testMock.get(), TestPhase::TestBody);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n==================\nUncaught Exception\n==================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(TestPhase::TestBody));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(TestUtil::NewlineConcat("",
         "  Type: std::runtime_error",
         "what(): \"" + s_stdExceptionMessage + "\"")));

      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Exception, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::TestBody;
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<runtime_error>(), s_stdExceptionMessage.c_str());
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST3X3(RunTestPhase_FunctionThrowsStdException_TestPhaseIsNotTestBody_WritesErrorMessageAndFailFastExitsWithCode1UnlessAlwaysExit0IsTrue,
      TestPhase testPhase, bool alwaysExit0, int expectedExitCode,
      TestPhase::Constructor, false, 1,
      TestPhase::Startup, false, 1,
      TestPhase::Cleanup, false, 1,
      TestPhase::Destructor, false, 1,
      TestPhase::Constructor, true, 0,
      TestPhase::Startup, true, 0,
      TestPhase::Cleanup, true, 0,
      TestPhase::Destructor, true, 0)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();

      ExpectStopwatchStartAndStopCalls();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.Return(_testPhaseSuffix.c_str());
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowStdException, _testMock.get(), testPhase);
      //
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      AssertStopwatchStartAndStopCalled();

      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(
         "\n==================\nUncaught Exception\n==================", Color::Red));
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      METALMOCK(_consoleMock->WriteMock.CalledOnceWith(_testPhaseSuffix));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(TestUtil::NewlineConcat("",
         "  Type: std::runtime_error",
         "what(): \"" + s_stdExceptionMessage + "\"")));

      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("\n===========\nFatal Error\n===========", Color::Red));
      const string expectedExitMessage = String::ConcatValues(
         "[ZenUnit] TestResult: A std::exception or std::exception subclass was thrown from a test class constructor, STARTUP function, or CLEANUP function.\n",
         "[ZenUnit]   ExitCode: ", expectedExitCode);
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedExitMessage, expectedExitCode));

      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Exception, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = testPhase;
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<runtime_error>(), s_stdExceptionMessage.c_str());
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   static void ThrowStdException(Test* test)
   {
      IS_NOT_NULLPTR(test);
      throw runtime_error(s_stdExceptionMessage.c_str());
   }

   TEST(RunTestPhase_FunctionThrowsMetalMockException_ReturnsExceptionResult)
   {
      ZenUnitArgs zenUnitArgs;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.Expect();

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

      const string exceptionTypeName = "MetalMock::UnexpectedCallException";
      const size_t expectedEqualsSignsLength =
         exceptionTypeName.size() + strlen(_testPhaseSuffix.c_str());
      const std::string expectedEqualsSigns(expectedEqualsSignsLength, '=');
      const string expectedExceptionNameAndTestPhaseSuffixLines = String::ConcatStrings("\n",
         expectedEqualsSigns, "\n",
         exceptionTypeName, _testPhaseSuffix, "\n",
         expectedEqualsSigns);
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
         expectedExceptionNameAndTestPhaseSuffixLines, Color::Red));

      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseSuffixMock.CalledOnceWith(testPhase));
      const string expectedWhat = MetalMock::UnexpectedCallException::MakeExceptionMessage("MetalMockedFunctionSignature");
      const string expectedTestPhaseSuffixAndWhatLines = String::ConcatStrings("what(): \"", expectedWhat, "\"");
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedTestPhaseSuffixAndWhatLines));

      METALMOCK(_caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccessMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_testPhaseRunner, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         TestOutcome::Exception, zenUnitArgs));

      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = testPhase;
      expectedTestPhaseResult.testOutcome = TestOutcome::Exception;
      expectedTestPhaseResult.anomalyOrException = make_shared<AnomalyOrException>(
         Type::GetName<MetalMock::UnexpectedCallException>(),
         MetalMock::UnexpectedCallException::MakeExceptionMessage("MetalMockedFunctionSignature").c_str());
      expectedTestPhaseResult.elapsedMicroseconds = _elapsedMicroseconds;
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
      const std::string testRunDurationInSeconds = _testRunStopwatchStopperMock->StopTestRunStopwatchAndGetElapsedSecondsMock.ReturnRandom();

      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _testPhaseStopwatchMock->StartMock.Expect();

      _consoleMock->WriteLineColorMock.Expect();

      _consoleMock->WriteColorMock.Expect();

      const string endTime = _watchMock->DateTimeNowMock.ReturnRandom();

      _consoleMock->WriteLineMock.Expect();

      const string testPhaseName = ZenUnit::Random<string>();
      _testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.Return(testPhaseName.c_str());

      _consoleMock->WriteLineAndExitMock.Expect();

      const TestPhase testPhase = ZenUnit::RandomEnum<TestPhase>(TestPhase::MaxValue);

      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      //
      const TestPhaseResult testPhaseResult = _testPhaseRunner.RunTestPhase(ThrowInt, _testMock.get(), testPhase);
      //
      METALMOCK(_testPhaseStopwatchMock->StartMock.CalledOnce());
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      METALMOCK(_testRunStopwatchStopperMock->StopTestRunStopwatchAndGetElapsedSecondsMock.CalledOnce());
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
         "\n==========================\nFatal ... Exception Thrown\n==========================\n", Color::Red));
      METALMOCK(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { ">>------> ", Color::Red },
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
         { "RandomSeed: --random-seed=" + to_string(globalZenUnitModeRandomSeed) },
         { " StartTime: " + zenUnitArgs.startDateTime },
         { "   EndTime: " + endTime },
         { "  Duration: " + testRunDurationInSeconds + " seconds" },
         { "   TestRun: " + to_string(globalZenUnitMode.currentTestRunNumber) + " of " + to_string(zenUnitArgs.testRuns) },
         { "    Result: Fatal ... exception thrown during test phase: " + testPhaseName }
      }));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      METALMOCK(_testPhaseTranslatorMock->TestPhaseToTestPhaseNameMock.CalledOnceWith(testPhase));
      const string expectedExitCodeLine = "  ExitCode: " + to_string(expectedExitCode);
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedExitCodeLine, expectedExitCode));
   }

   TEST(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsFalse_DoesNothing)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.failFast = false;
      const TestOutcome testOutcome = ZenUnit::RandomEnum<TestOutcome>(TestOutcome::MaxValue);
      //
      _testPhaseRunner.FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(testOutcome, zenUnitArgs);
   }

   TEST(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsTrue_TestOutcomeIsSuccess_DoesNothing)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.failFast = false;
      const TestOutcome testOutcome = TestOutcome::Success;
      //
      _testPhaseRunner.FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(testOutcome, zenUnitArgs);
   }

   TEST3X3(FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess_FailFastIsTrue_TestPhaseResultIsNotSuccess_WritesFailFastMessage_ExitsWithCode1UnlessAlwaysExit0IsTrue,
      TestOutcome testOutcome, bool alwaysExit0, int expectedExitCode,
      TestOutcome::SuccessButPastDeadline, false, 1,
      TestOutcome::Anomaly, false, 1,
      TestOutcome::Exception, false, 1,
      TestOutcome::SuccessButPastDeadline, true, 0,
      TestOutcome::Anomaly, true, 0,
      TestOutcome::Exception, true, 0)
   {
      _consoleMock->WriteLineAndExitMock.Expect();
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.failFast = true;
      zenUnitArgs.alwaysExit0 = alwaysExit0;

      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      //
      _testPhaseRunner.FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(testOutcome, zenUnitArgs);
      //
      const string expectedFailFastMessage = String::ConcatValues("\n",
         "[ZenUnit] A test failed in --fail-fast mode.\n",
         "[ZenUnit]   Completed: ", zenUnitArgs.commandLine, "\n",
         "[ZenUnit]  RandomSeed: --random-seed=", globalZenUnitModeRandomSeed, "\n",
         "[ZenUnit]     TestRun: ", globalZenUnitMode.currentTestRunNumber, " of ", zenUnitArgs.testRuns, "\n",
         "[ZenUnit]    ExitCode: ", expectedExitCode);
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedFailFastMessage, expectedExitCode));
   }

   RUN_TESTS(TestPhaseRunnerTests)

   int TestPhaseRunnerTests::s_numberOfCallsToFunctionThatDoesNotThrowAnException;
   string TestPhaseRunnerTests::s_stdExceptionMessage;
   Anomaly TestPhaseRunnerTests::s_anomaly;
}
