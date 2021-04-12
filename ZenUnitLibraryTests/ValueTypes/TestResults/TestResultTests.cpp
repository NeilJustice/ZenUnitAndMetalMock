#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestFailureNumbererMock.h"

namespace ZenUnit
{
   TESTS(TestResultTests)
   AFACT(DefaultConstructor_SetsFieldsTo0_SetsWatchFunction)
   FACTS(SixArgConstructor_SetsFields_SetsWatchFunction)
   FACTS(ConstructorFail_ReturnsExpectedTestResult)
   FACTS(StartupFail_ReturnsExpectedTestResult)
   AFACT(ConstructorDestructorSuccess_ReturnsExpectedTestResult);
   FACTS(WriteLineOKIfSuccess_PrintsOKIfTestOutcomeSuccess)
   AFACT(PrintIfFailure_TestOutcomeIsSuccess_PrintsNothing)
   FACTS(PrintIfFailure_TestOutcomeIsAnomaly_PrintsExpected)
   FACTS(PrintIfFailure_TestOutcomeIsException_PrintsExpected)
   FACTS(PrintIfFailure_TestOutcomeIsSuccessButPastDeadline_PrintsExpectedErrorMessage)
   FACTS(PrintIfFailure_TestOutcomeIsInvalid_ThrowsInvalidArgument)
   FACTS(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseNumberIfTestCaseNumberNotMaxValue)
   EVIDENCE

   TestResult _testResult;
   // Mocks
   ConsoleMock _consoleMock;
   TestFailureNumbererMock _testFailureNumbererMock;
   METALMOCK_NONVOID1_STATIC(string, ZenUnit::Watch, MicrosecondsToTwoDecimalPlaceMillisecondsString, long long)
   // Testing Fields
   TestPhaseResult ConstructorTestPhaseResult;
   TestPhaseResult StartupTestPhaseResult;
   TestPhaseResult DestructorTestPhaseResult;
   const FullTestName FullTestNameValue = FullTestName("ClassName", "TestClassName", ZenUnit::Random<unsigned char>());

   const unsigned MaxTestMilliseconds = 1 + 2 + 3 + 4 + 5;

   class TestResult_WriteTestCaseNumberIfAnyMocked : public Metal::Mock<TestResult>
   {
   public:
      METALMOCK_VOID2_CONST(WriteTestCaseNumberIfAny, const Console*, size_t)
   } _testResult_WriteTestCaseNumberIfAnyMocked;

   STARTUP
   {
      // Mocks
      _testResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString = BIND_1ARG_METALMOCK_OBJECT(MicrosecondsToTwoDecimalPlaceMillisecondsStringMock);
      // Testing Fields
      ConstructorTestPhaseResult = TestPhaseResult(TestPhase::Constructor);
      ConstructorTestPhaseResult.microseconds = 1000;
      StartupTestPhaseResult = TestPhaseResult(TestPhase::Startup);
      StartupTestPhaseResult.microseconds = 2000;
      DestructorTestPhaseResult = TestPhaseResult(TestPhase::Destructor);
      DestructorTestPhaseResult.microseconds = 3000;
      _testResult.fullTestName = FullTestNameValue;
   }

   TEST(DefaultConstructor_SetsFieldsTo0_SetsWatchFunction)
   {
      const TestResult defaultTestResult;
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString, defaultTestResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
      TestResult expectedDefaultTestResult;
      expectedDefaultTestResult.fullTestName = FullTestName();
      expectedDefaultTestResult.constructorTestPhaseResult = TestPhaseResult();
      expectedDefaultTestResult.startupTestPhaseResult = TestPhaseResult();
      expectedDefaultTestResult.testBodyTestPhaseResult = TestPhaseResult();
      expectedDefaultTestResult.cleanupTestPhaseResult = TestPhaseResult();
      expectedDefaultTestResult.destructorTestPhaseResult = TestPhaseResult();
      expectedDefaultTestResult.responsibleTestPhaseResultField = nullptr;
      expectedDefaultTestResult.testOutcome = TestOutcome::Unset;
      expectedDefaultTestResult.testCaseNumber = numeric_limits<size_t>::max();
      expectedDefaultTestResult.totalTestCases = 0;
      expectedDefaultTestResult.microseconds = 0;
      ARE_EQUAL(expectedDefaultTestResult, defaultTestResult);
   }

   TEST6X6(SixArgConstructor_SetsFields_SetsWatchFunction,
      TestOutcome testBodyOutcome,
      TestOutcome cleanupOutcome,
      unsigned maxTestMilliseconds,
      int relativeMicroseconds,
      TestOutcome expectedOverallOutcome,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestOutcome::Success, TestOutcome::Success, 0u, 0, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, 0u, 1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, -1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 0, TestOutcome::Success, nullptr,

      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::SuccessButPastDeadline, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 2, TestOutcome::SuccessButPastDeadline, nullptr,

      TestOutcome::Exception, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyTestPhaseResult,
      TestOutcome::Exception, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyTestPhaseResult,
      TestOutcome::Exception, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyTestPhaseResult,

      TestOutcome::Success, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupTestPhaseResult,
      TestOutcome::Anomaly, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupTestPhaseResult,

      TestOutcome::Anomaly, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyTestPhaseResult,
      TestOutcome::Success, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::cleanupTestPhaseResult,
      TestOutcome::Anomaly, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyTestPhaseResult)
   {
      TestPhaseResult testBodyTestPhaseResult(TestPhase::TestBody);
      testBodyTestPhaseResult.testOutcome = testBodyOutcome;
      testBodyTestPhaseResult.microseconds = 4000;
      TestPhaseResult cleanupTestPhaseResult(TestPhase::Cleanup);
      cleanupTestPhaseResult.testOutcome = cleanupOutcome;
      cleanupTestPhaseResult.microseconds = static_cast<unsigned>(5000 + relativeMicroseconds);

      METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitArgs, GetArgs)

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.maxTestMilliseconds = maxTestMilliseconds;
      if (expectedOverallOutcome == TestOutcome::Success || expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgsMock.Return(zenUnitArgs);
      }
      const function<const ZenUnitArgs&()> getArgsMockFunction = BIND_0ARG_METALMOCK_OBJECT(GetArgsMock);
      //
      const TestResult testResult(
         FullTestNameValue,
         ConstructorTestPhaseResult,
         StartupTestPhaseResult,
         testBodyTestPhaseResult,
         cleanupTestPhaseResult,
         DestructorTestPhaseResult,
         getArgsMockFunction);
      //
      if (expectedOverallOutcome == TestOutcome::Success || expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgsMock.CalledOnce();
      }
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString, testResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorTestPhaseResult = ConstructorTestPhaseResult;
      expectedTestResult.startupTestPhaseResult = StartupTestPhaseResult;
      expectedTestResult.testBodyTestPhaseResult = testBodyTestPhaseResult;
      expectedTestResult.cleanupTestPhaseResult = cleanupTestPhaseResult;
      expectedTestResult.destructorTestPhaseResult = DestructorTestPhaseResult;
      expectedTestResult.responsibleTestPhaseResultField = expectedResponsibleTestPhaseResultField;
      expectedTestResult.testOutcome = expectedOverallOutcome;
      expectedTestResult.testCaseNumber = numeric_limits<size_t>::max();
      expectedTestResult.totalTestCases = 0;
      expectedTestResult.microseconds = static_cast<unsigned>(MaxTestMilliseconds * 1000 + relativeMicroseconds);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   TEST2X2(ConstructorFail_ReturnsExpectedTestResult,
      TestOutcome constructorOutcome, TestOutcome expectedTestResultOutcome,
      TestOutcome::Anomaly, TestOutcome::Anomaly,
      TestOutcome::Exception, TestOutcome::Exception)
   {
      ConstructorTestPhaseResult.testOutcome = constructorOutcome;
      //
      const TestResult constructorFailTestResult = TestResult::ConstructorFail(FullTestNameValue, ConstructorTestPhaseResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorTestPhaseResult = ConstructorTestPhaseResult;
      expectedTestResult.responsibleTestPhaseResultField = &TestResult::constructorTestPhaseResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.microseconds = ConstructorTestPhaseResult.microseconds;
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST2X2(StartupFail_ReturnsExpectedTestResult,
      TestOutcome startupOutcome, TestOutcome expectedTestResultOutcome,
      TestOutcome::Anomaly, TestOutcome::Anomaly,
      TestOutcome::Exception, TestOutcome::Exception)
   {
      StartupTestPhaseResult.testOutcome = startupOutcome;
      //
      const TestResult startupFailTestResult = TestResult::StartupFail(
         FullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult, DestructorTestPhaseResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorTestPhaseResult = ConstructorTestPhaseResult;
      expectedTestResult.startupTestPhaseResult = StartupTestPhaseResult;
      expectedTestResult.destructorTestPhaseResult = DestructorTestPhaseResult;
      expectedTestResult.responsibleTestPhaseResultField = &TestResult::startupTestPhaseResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.microseconds =
         ConstructorTestPhaseResult.microseconds + StartupTestPhaseResult.microseconds + DestructorTestPhaseResult.microseconds;
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(ConstructorDestructorSuccess_ReturnsExpectedTestResult)
   {
      TestPhaseResult constructorTestPhaseResult(TestPhase::Constructor);
      constructorTestPhaseResult.microseconds = 10;
      TestPhaseResult destructorTestPhaseResult(TestPhase::Destructor);
      destructorTestPhaseResult.microseconds = 20;
      //
      const TestResult testResult = TestResult::ConstructorDestructorSuccess(FullTestNameValue, constructorTestPhaseResult, destructorTestPhaseResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.testOutcome = TestOutcome::Success;
      expectedTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
      expectedTestResult.destructorTestPhaseResult = destructorTestPhaseResult;
      expectedTestResult.microseconds = constructorTestPhaseResult.microseconds + destructorTestPhaseResult.microseconds;
      expectedTestResult.responsibleTestPhaseResultField = nullptr;
      ARE_EQUAL(expectedTestResult, testResult);
   }

   TEST2X2(WriteLineOKIfSuccess_PrintsOKIfTestOutcomeSuccess,
      TestOutcome testOutcome, bool expectWriteLineOK,
      TestOutcome::Success, true,
      TestOutcome::Anomaly, false,
      TestOutcome::Exception, false,
      TestOutcome::SuccessButPastDeadline, false,
      TestOutcome::Unset, false)
   {
      _testResult.testOutcome = testOutcome;
      string twoDecimalPlaceMillisecondsString;
      if (expectWriteLineOK)
      {
         _consoleMock.WriteColorMock.Expect();
         _consoleMock.WriteLineMock.Expect();
         twoDecimalPlaceMillisecondsString = MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();
      }
      const unsigned microseconds = ZenUnit::Random<unsigned>();
      _testResult.microseconds = microseconds;
      //
      _testResult.WriteLineOKIfSuccess(&_consoleMock);
      //
      if (expectWriteLineOK)
      {
         METALMOCK(_consoleMock.WriteColorMock.CalledOnceWith("OK ", Color::Green));
         METALMOCK(MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.CalledOnceWith(microseconds));
         METALMOCK(_consoleMock.WriteLineMock.CalledOnceWith(twoDecimalPlaceMillisecondsString));
      }
   }

   TEST(PrintIfFailure_TestOutcomeIsSuccess_PrintsNothing)
   {
      _testResult.testOutcome = TestOutcome::Success;
      _testResult.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   }

   TEST3X3(PrintIfFailure_TestOutcomeIsAnomaly_PrintsExpected,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorTestPhaseResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupTestPhaseResult, TestPhase::Startup, " in STARTUP function",
      &TestResult::testBodyTestPhaseResult, TestPhase::TestBody, "",
      &TestResult::cleanupTestPhaseResult, TestPhase::Cleanup, " in CLEANUP function")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Anomaly;

      const string anomalyWhy = Random<string>();
      Anomaly anomaly;
      anomaly.why = anomalyWhy;
      (_testResult_WriteTestCaseNumberIfAnyMocked.*expectedResponsibleTestPhaseResultField).anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*expectedResponsibleTestPhaseResultField).testPhase = testPhase;

      _testResult_WriteTestCaseNumberIfAnyMocked.responsibleTestPhaseResultField = expectedResponsibleTestPhaseResultField;

      const string numberedTestFailureArrow = _testFailureNumbererMock.NextNumberedTestFailureArrowMock.ReturnRandom();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      METALMOCK(_testFailureNumbererMock.NextNumberedTestFailureArrowMock.CalledOnce());
      METALMOCK(_consoleMock.WriteMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { expectedTestPhaseSuffix }
      }));
      METALMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      METALMOCK(_consoleMock.WriteLineColorMock.CalledOnceWith(numberedTestFailureArrow, Color::Red));
      METALMOCK(_consoleMock.WriteLineMock.CalledOnceWith(anomalyWhy));
      METALMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST3X3(PrintIfFailure_TestOutcomeIsException_PrintsExpected,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorTestPhaseResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupTestPhaseResult, TestPhase::Startup, " in STARTUP function",
      &TestResult::testBodyTestPhaseResult, TestPhase::TestBody, "",
      &TestResult::cleanupTestPhaseResult, TestPhase::Cleanup, " in CLEANUP function")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = ZenUnit::Random<FullTestName>();
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Exception;

      const string exceptionTypeName = Random<string>();
      const string exceptionWhatString = Random<string>();
      const char* const exceptionWhat = exceptionWhatString.c_str();
      (_testResult_WriteTestCaseNumberIfAnyMocked.*expectedResponsibleTestPhaseResultField).anomalyOrException = 
         make_shared<AnomalyOrException>(&exceptionTypeName, exceptionWhat);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*expectedResponsibleTestPhaseResultField).testPhase = testPhase;
      _testResult_WriteTestCaseNumberIfAnyMocked.responsibleTestPhaseResultField = expectedResponsibleTestPhaseResultField;

      const string numberedTestFailureArrow = _testFailureNumbererMock.NextNumberedTestFailureArrowMock.ReturnRandom();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      METALMOCK(_testFailureNumbererMock.NextNumberedTestFailureArrowMock.CalledOnce());
      METALMOCK(_consoleMock.WriteMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { expectedTestPhaseSuffix }
      }));
      METALMOCK(_consoleMock.WriteLineColorMock.CalledAsFollows(
      {
         { numberedTestFailureArrow, Color::Red },
         { "\n==================\nUncaught Exception\n==================", Color::Red }
      }));
      METALMOCK(_consoleMock.WriteLineMock.CalledOnceWith(
         "  Type: " + exceptionTypeName + "\n"
         "what(): \""s + exceptionWhat + "\""));
      METALMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      METALMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST2X2(PrintIfFailure_TestOutcomeIsSuccessButPastDeadline_PrintsExpectedErrorMessage,
      unsigned elapsedTestMicroseconds, unsigned expectedElapsedTestMilliseconds,
      10000U, 10U,
      100000U, 100U)
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = ZenUnit::Random<FullTestName>();
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::SuccessButPastDeadline;
      _testResult_WriteTestCaseNumberIfAnyMocked.microseconds = elapsedTestMicroseconds;

      const string numberedTestFailureArrow = _testFailureNumbererMock.NextNumberedTestFailureArrowMock.ReturnRandom();

      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      METALMOCK(_testFailureNumbererMock.NextNumberedTestFailureArrowMock.CalledOnce());
      METALMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.CalledOnceWith(
         &_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      METALMOCK(_consoleMock.WriteLineColorMock.CalledOnceWith(numberedTestFailureArrow, Color::Red));
      METALMOCK(_consoleMock.WriteLineMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { "\nFailed because test took longer than --max-test-milliseconds=" + to_string(expectedElapsedTestMilliseconds) + " milliseconds" }
      }));
      METALMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST1X1(PrintIfFailure_TestOutcomeIsInvalid_ThrowsInvalidArgument,
      TestOutcome invalidTestOutcome,
      TestOutcome::Unset,
      TestOutcome::MaxValue)
   {
      ConsoleMock consoleMock;
      TestFailureNumbererMock testFailureNumbererMock;
      _testResult.testOutcome = invalidTestOutcome;
      //
      THROWS_EXCEPTION(_testResult.PrintIfFailure(&consoleMock, &testFailureNumbererMock),
         invalid_argument, "Invalid TestOutcome: " + to_string(static_cast<int>(invalidTestOutcome)));
   }

   TEST2X2(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseNumberIfTestCaseNumberNotMaxValue,
      size_t testCaseNumber, bool expectConsoleWriteLine,
      numeric_limits<size_t>::max(), false,
      1ULL, true,
      2ULL, true,
      3ULL, true)
   {
      if (expectConsoleWriteLine)
      {
         _consoleMock.WriteMock.Expect();
      }
      _testResult.totalTestCases = ZenUnit::Random<size_t>();
      //
      _testResult.WriteTestCaseNumberIfAny(&_consoleMock, testCaseNumber);
      //
      if (expectConsoleWriteLine)
      {
         const string expectedErrorMessage = String::Concat(" test case ", testCaseNumber, '/', _testResult.totalTestCases);
         METALMOCK(_consoleMock.WriteMock.CalledOnceWith(expectedErrorMessage));
      }
   }

   RUN_TESTS(TestResultTests)
}
