#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestFailureNumbererMock.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestResultTests)
   AFACT(DefaultConstructor_SetsFieldsTo0_SetsWatchFunction)
   FACTS(SixArgConstructor_SetsFields_SetsWatchFunction)
   FACTS(ConstructorFail_ReturnsExpectedTestResult)
   FACTS(StartupFail_ReturnsExpectedTestResult)
   AFACT(CtorDtorSuccess_ReturnsExpectedTestResult);
   FACTS(WriteLineOKIfSuccess_PrintsOKIfTestOutcomeSuccess)
   AFACT(PrintIfFailure_Success_PrintsNothing)
   FACTS(PrintIfFailure_Anomaly_PrintsExpected)
   FACTS(PrintIfFailure_Exception_PrintsExpected)
   AFACT(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
   AFACT(PrintIfFailure_InvalidOutcome_Throws)
   FACTS(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseNumberIfTestCaseNumberNotMaxValue)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TestResult _testResult;
   TestPhaseResult ConstructorTestPhaseResult;
   TestPhaseResult StartupTestPhaseResult;
   TestPhaseResult DestructorTestPhaseResult;
   ConsoleMock _consoleMock;
   TestFailureNumbererMock _testFailureNumbererMock;
   const FullTestName FullTestNameValue = FullTestName("ClassName", "TestClassName", ZenUnit::Random<unsigned char>());
   ZENMOCK_NONVOID1_STATIC(string, ZenUnit::Watch, MicrosecondsToTwoDecimalPlaceMillisecondsString, unsigned)

   const unsigned MaxTestMilliseconds = 1 + 2 + 3 + 4 + 5;

   class TestResult_WriteTestCaseNumberIfAnyMocked : public Zen::Mock<TestResult>
   {
   public:
      ZENMOCK_VOID2_CONST(WriteTestCaseNumberIfAny, const Console*, size_t)
   } _testResult_WriteTestCaseNumberIfAnyMocked;

   STARTUP
   {
      ConstructorTestPhaseResult = TestPhaseResult(TestPhase::Constructor);
      ConstructorTestPhaseResult.microseconds = 1000;
      StartupTestPhaseResult = TestPhaseResult(TestPhase::Startup);
      StartupTestPhaseResult.microseconds = 2000;
      DestructorTestPhaseResult = TestPhaseResult(TestPhase::Destructor);
      DestructorTestPhaseResult.microseconds = 3000;
      _testResult.fullTestName = FullTestNameValue;
      _testResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString =
         BIND_1ARG_ZENMOCK_OBJECT(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject);
   }

   TEST(DefaultConstructor_SetsFieldsTo0_SetsWatchFunction)
   {
      const TestResult defaultTestResult;
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString,
         defaultTestResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
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
      unsigned maxtestmilliseconds,
      int relativeMicroseconds,
      TestOutcome expectedOverallOutcome,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestOutcome::Success, TestOutcome::Success, 0, 0, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, 0, 1, TestOutcome::Success, nullptr,
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
      cleanupTestPhaseResult.microseconds = 5000 + relativeMicroseconds;

      ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitArgs, GetArgs)

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.maxtestmilliseconds = maxtestmilliseconds;
      if (expectedOverallOutcome == TestOutcome::Success ||
         expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgs_ZenMockObject.Return(zenUnitArgs);
      }
      const function<const ZenUnitArgs&()> getArgsMockFunction = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
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
      if (expectedOverallOutcome == TestOutcome::Success ||
         expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgs_ZenMockObject.CalledOnce();
      }
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString,
         testResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
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
      expectedTestResult.microseconds = MaxTestMilliseconds * 1000 + relativeMicroseconds;
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

   TEST(CtorDtorSuccess_ReturnsExpectedTestResult)
   {
      TestPhaseResult constructorTestPhaseResult(TestPhase::Constructor);
      constructorTestPhaseResult.microseconds = 10;
      TestPhaseResult destructorTestPhaseResult(TestPhase::Destructor);
      destructorTestPhaseResult.microseconds = 20;
      //
      const TestResult testResult = TestResult::CtorDtorSuccess(FullTestNameValue, constructorTestPhaseResult, destructorTestPhaseResult);
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
      std::string twoDecimalPlaceMillisecondsString;
      if (expectWriteLineOK)
      {
         _consoleMock.WriteColorMock.Expect();
         _consoleMock.WriteLineMock.Expect();
         twoDecimalPlaceMillisecondsString = MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.ReturnRandom();
      }
      const unsigned microseconds = ZenUnit::Random<unsigned>();
      _testResult.microseconds = microseconds;
      //
      _testResult.WriteLineOKIfSuccess(&_consoleMock);
      //
      if (expectWriteLineOK)
      {
         ZENMOCK(_consoleMock.WriteColorMock.CalledOnceWith("OK ", Color::Green));
         ZENMOCK(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.CalledOnceWith(microseconds));
         ZENMOCK(_consoleMock.WriteLineMock.CalledOnceWith(twoDecimalPlaceMillisecondsString));
      }
   }

   TEST(PrintIfFailure_Success_PrintsNothing)
   {
      _testResult.testOutcome = TestOutcome::Success;
      _testResult.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   }

   TEST3X3(PrintIfFailure_Anomaly_PrintsExpected,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorTestPhaseResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupTestPhaseResult, TestPhase::Startup, " in STARTUP",
      &TestResult::testBodyTestPhaseResult, TestPhase::TestBody, "",
      &TestResult::cleanupTestPhaseResult, TestPhase::Cleanup, " in CLEANUP")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Anomaly;

      const string anomalyWhy = Random<string>();
      Anomaly anomaly;
      anomaly.why = anomalyWhy;
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleTestPhaseResultField).anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleTestPhaseResultField).testPhase = testPhase;

      _testResult_WriteTestCaseNumberIfAnyMocked.responsibleTestPhaseResultField = expectedResponsibleTestPhaseResultField;

      const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZENMOCK(_testFailureNumbererMock.NextMock.CalledOnce());
      ZENMOCK(_consoleMock.WriteMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { expectedTestPhaseSuffix }
      }));
      ZENMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZENMOCK(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
      ZENMOCK(_consoleMock.WriteLineMock.CalledOnceWith(anomalyWhy));
      ZENMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST3X3(PrintIfFailure_Exception_PrintsExpected,
      TestPhaseResult TestResult::* expectedResponsibleTestPhaseResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorTestPhaseResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupTestPhaseResult, TestPhase::Startup, " in STARTUP",
      &TestResult::testBodyTestPhaseResult, TestPhase::TestBody, "",
      &TestResult::cleanupTestPhaseResult, TestPhase::Cleanup, " in CLEANUP")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Exception;

      const string exceptionTypeName = Random<string>();
      const string exceptionWhatString = Random<string>();
      const char* const exceptionWhat = exceptionWhatString.c_str();
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleTestPhaseResultField).anomalyOrException = make_shared<AnomalyOrException>(&exceptionTypeName, exceptionWhat);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleTestPhaseResultField).testPhase = testPhase;
      _testResult_WriteTestCaseNumberIfAnyMocked.
         responsibleTestPhaseResultField = expectedResponsibleTestPhaseResultField;

      const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZENMOCK(_testFailureNumbererMock.NextMock.CalledOnce());
      ZENMOCK(_consoleMock.WriteMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { expectedTestPhaseSuffix }
      }));
      ZENMOCK(_consoleMock.WriteLineColorMock.CalledAsFollows(
      {
         { testFailureNumber, Color::Red },
         { "\nUncaught Exception Thrown", Color::Red }
      }));
      ZENMOCK(_consoleMock.WriteLineMock.CalledOnceWith(
         "  Type: " + exceptionTypeName + "\n"
         "what(): \""s + exceptionWhat + "\""));
      ZENMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZENMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::SuccessButPastDeadline;
      _testResult_WriteTestCaseNumberIfAnyMocked.microseconds = 10000;

      const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewLineMock.Expect();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber = ZenUnit::Random<size_t>();
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZENMOCK(_testFailureNumbererMock.NextMock.CalledOnce());
      ZENMOCK(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZENMOCK(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
      ZENMOCK(_consoleMock.WriteLineMock.CalledAsFollows(
      {
         { _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value() },
         { "\nFailed because test took longer than --max-test-ms=10 milliseconds"s }
      }));
      ZENMOCK(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST(PrintIfFailure_InvalidOutcome_Throws)
   {
      ConsoleMock consoleMock;
      TestFailureNumbererMock testFailureNumbererMock;
      _testResult.testOutcome = TestOutcome::Unset;
      THROWS(_testResult.PrintIfFailure(&consoleMock, &testFailureNumbererMock),
         invalid_argument, "Invalid TestOutcome::Unset");
   }

   TEST2X2(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseNumberIfTestCaseNumberNotMaxValue,
      size_t testCaseNumber, bool expectConsoleWriteLine,
      numeric_limits<size_t>::max(), false,
      1, true,
      2, true,
      3, true)
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
         ZENMOCK(_consoleMock.WriteMock.CalledOnceWith(" test case " + to_string(testCaseNumber) + "/" + to_string(_testResult.totalTestCases)));
      }
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestResult);
      EQUALIZER_THROWS(TestResult, fullTestName, FullTestName("ClassName", "TestName", 0));

      TestPhaseResult nonDefaultConstructorTestPhaseResult;
      nonDefaultConstructorTestPhaseResult.testPhase = TestPhase::Constructor;
      EQUALIZER_THROWS(TestResult, constructorTestPhaseResult, nonDefaultConstructorTestPhaseResult);

      TestPhaseResult nonDefaultStartupTestPhaseResult;
      nonDefaultStartupTestPhaseResult.testPhase = TestPhase::Startup;
      EQUALIZER_THROWS(TestResult, startupTestPhaseResult, nonDefaultStartupTestPhaseResult);

      TestPhaseResult nonDefaultTestBodyTestPhaseResult;
      nonDefaultTestBodyTestPhaseResult.testPhase = TestPhase::TestBody;
      EQUALIZER_THROWS(TestResult, testBodyTestPhaseResult, nonDefaultTestBodyTestPhaseResult);

      TestPhaseResult nonDefaultCleanupTestPhaseResult;
      nonDefaultCleanupTestPhaseResult.testPhase = TestPhase::Cleanup;
      EQUALIZER_THROWS(TestResult, cleanupTestPhaseResult, nonDefaultCleanupTestPhaseResult);

      TestPhaseResult nonDefaultDestructorTestPhaseResult;
      nonDefaultDestructorTestPhaseResult.testPhase = TestPhase::Destructor;
      EQUALIZER_THROWS(TestResult, destructorTestPhaseResult, nonDefaultDestructorTestPhaseResult);

      EQUALIZER_THROWS(TestResult, responsibleTestPhaseResultField, &TestResult::constructorTestPhaseResult);
      EQUALIZER_THROWS(TestResult, testOutcome, TestOutcome::Anomaly);
      EQUALIZER_THROWS(TestResult, testCaseNumber, size_t(10));
      EQUALIZER_THROWS(TestResult, totalTestCases, size_t(20));
      EQUALIZER_THROWS(TestResult, microseconds, 30u);
   }

   RUN_TESTS(TestResultTests)
}
