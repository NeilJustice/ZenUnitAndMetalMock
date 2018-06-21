#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestFailureNumbererMock.h"

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
   CallResult ConstructorCallResult;
   CallResult StartupCallResult;
   CallResult DestructorCallResult;
   ConsoleMock _consoleMock;
   TestFailureNumbererMock _testFailureNumbererMock;
   const FullTestName FullTestNameValue = FullTestName("ClassName", "TestClassName", ZenUnit::Random<unsigned char>());
   ZENMOCK_NONVOID1_STATIC(string, ZenUnit::Watch, MicrosecondsToTwoDecimalPlaceMillisecondsString, unsigned);

   const unsigned MaxTestMilliseconds = 1 + 2 + 3 + 4 + 5;

   struct TestResult_WriteTestCaseNumberIfAnyMocked : public Zen::Mock<TestResult>
   {
      ZENMOCK_VOID2_CONST(WriteTestCaseNumberIfAny, const Console*, size_t)
   } _testResult_WriteTestCaseNumberIfAnyMocked;

   STARTUP
   {
      ConstructorCallResult = CallResult(TestPhase::Constructor);
      ConstructorCallResult.microseconds = 1000;
      StartupCallResult = CallResult(TestPhase::Startup);
      StartupCallResult.microseconds = 2000;
      DestructorCallResult = CallResult(TestPhase::Destructor);
      DestructorCallResult.microseconds = 3000;
      _testResult.fullTestName = FullTestNameValue;
      _testResult.call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString =
         BIND_1ARG_ZENMOCK_OBJECT(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject);
   }

   TEST(DefaultConstructor_SetsFieldsTo0_SetsWatchFunction)
   {
      const TestResult defaultTestResult;
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString,
         defaultTestResult.call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
      TestResult expectedDefaultTestResult;
      expectedDefaultTestResult.fullTestName = FullTestName();
      expectedDefaultTestResult.constructorCallResult = CallResult();
      expectedDefaultTestResult.startupCallResult = CallResult();
      expectedDefaultTestResult.testBodyCallResult = CallResult();
      expectedDefaultTestResult.cleanupCallResult = CallResult();
      expectedDefaultTestResult.destructorCallResult = CallResult();
      expectedDefaultTestResult.responsibleCallResultField = nullptr;
      expectedDefaultTestResult.testOutcome = TestOutcome::Unset;
      expectedDefaultTestResult.testCaseNumber = numeric_limits<size_t>::max();
      expectedDefaultTestResult.microseconds = 0;
      ARE_EQUAL(expectedDefaultTestResult, defaultTestResult);
   }

   TEST6X6(SixArgConstructor_SetsFields_SetsWatchFunction,
      TestOutcome testBodyOutcome,
      TestOutcome cleanupOutcome,
      unsigned maxtestmilliseconds,
      int relativeMicroseconds,
      TestOutcome expectedOverallOutcome,
      CallResult TestResult::* expectedResponsibleCallResultField,
      TestOutcome::Success, TestOutcome::Success, 0, 0, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, 0, 1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, -1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 0, TestOutcome::Success, nullptr,

      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::SuccessButPastDeadline, nullptr,
      TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 2, TestOutcome::SuccessButPastDeadline, nullptr,

      TestOutcome::Exception, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
      TestOutcome::Exception, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
      TestOutcome::Exception, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,

      TestOutcome::Success, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,
      TestOutcome::Anomaly, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,

      TestOutcome::Anomaly, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult,
      TestOutcome::Success, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::cleanupCallResult,
      TestOutcome::Anomaly, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult)
   {
      CallResult testBodyCallResult(TestPhase::TestBody);
      testBodyCallResult.testOutcome = testBodyOutcome;
      testBodyCallResult.microseconds = 4000;
      CallResult cleanupCallResult(TestPhase::Cleanup);
      cleanupCallResult.testOutcome = cleanupOutcome;
      cleanupCallResult.microseconds = 5000 + relativeMicroseconds;

      ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitArgs, GetArgs);

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
         ConstructorCallResult,
         StartupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         DestructorCallResult,
         getArgsMockFunction);
      //
      if (expectedOverallOutcome == TestOutcome::Success ||
         expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgs_ZenMockObject.CalledOnce();
      }
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString,
         testResult.call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.startupCallResult = StartupCallResult;
      expectedTestResult.testBodyCallResult = testBodyCallResult;
      expectedTestResult.cleanupCallResult = cleanupCallResult;
      expectedTestResult.destructorCallResult = DestructorCallResult;
      expectedTestResult.responsibleCallResultField = expectedResponsibleCallResultField;
      expectedTestResult.testOutcome = expectedOverallOutcome;
      expectedTestResult.testCaseNumber = numeric_limits<size_t>::max();
      expectedTestResult.microseconds = MaxTestMilliseconds * 1000 + relativeMicroseconds;
      ARE_EQUAL(expectedTestResult, testResult);
   }

   TEST2X2(ConstructorFail_ReturnsExpectedTestResult,
      TestOutcome constructorOutcome, TestOutcome expectedTestResultOutcome,
      TestOutcome::Anomaly, TestOutcome::Anomaly,
      TestOutcome::Exception, TestOutcome::Exception)
   {
      ConstructorCallResult.testOutcome = constructorOutcome;
      //
      const TestResult constructorFailTestResult =
         TestResult::ConstructorFail(FullTestNameValue, ConstructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.microseconds = ConstructorCallResult.microseconds;
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST2X2(StartupFail_ReturnsExpectedTestResult,
      TestOutcome startupOutcome, TestOutcome expectedTestResultOutcome,
      TestOutcome::Anomaly, TestOutcome::Anomaly,
      TestOutcome::Exception, TestOutcome::Exception)
   {
      StartupCallResult.testOutcome = startupOutcome;
      //
      const TestResult startupFailTestResult = TestResult::StartupFail(
         FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.startupCallResult = StartupCallResult;
      expectedTestResult.destructorCallResult = DestructorCallResult;
      expectedTestResult.responsibleCallResultField = &TestResult::startupCallResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.microseconds =
         ConstructorCallResult.microseconds + StartupCallResult.microseconds + DestructorCallResult.microseconds;
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(CtorDtorSuccess_ReturnsExpectedTestResult)
   {
      CallResult constructorCallResult(TestPhase::Constructor);
      constructorCallResult.microseconds = 10;
      CallResult destructorCallResult(TestPhase::Destructor);
      destructorCallResult.microseconds = 20;
      //
      const TestResult testResult = TestResult::CtorDtorSuccess(
         FullTestNameValue, constructorCallResult, destructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.fullTestName = FullTestNameValue;
      expectedTestResult.testOutcome = TestOutcome::Success;
      expectedTestResult.constructorCallResult = constructorCallResult;
      expectedTestResult.destructorCallResult = destructorCallResult;
      expectedTestResult.microseconds = constructorCallResult.microseconds + destructorCallResult.microseconds;
      expectedTestResult.responsibleCallResultField = nullptr;
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
      std::string threeDecimalPlaceMillisecondsString;
      if (expectWriteLineOK)
      {
         _consoleMock.WriteColorMock.Expect();
         _consoleMock.WriteLineMock.Expect();
         threeDecimalPlaceMillisecondsString = MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.ReturnRandom();
      }
      const unsigned microseconds = ZenUnit::Random<unsigned>();
      _testResult.microseconds = microseconds;
      //
      _testResult.WriteLineOKIfSuccess(&_consoleMock);
      //
      if (expectWriteLineOK)
      {
         ZEN(_consoleMock.WriteColorMock.CalledOnceWith("OK ", Color::Green));
         ZEN(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.CalledOnceWith(microseconds));
         ZEN(_consoleMock.WriteLineMock.CalledOnceWith(threeDecimalPlaceMillisecondsString));
      }
   }

   TEST(PrintIfFailure_Success_PrintsNothing)
   {
      _testResult.testOutcome = TestOutcome::Success;
      _testResult.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   }

   TEST3X3(PrintIfFailure_Anomaly_PrintsExpected,
      CallResult TestResult::* expectedResponsibleCallResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorCallResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupCallResult, TestPhase::Startup, " in STARTUP",
      &TestResult::testBodyCallResult, TestPhase::TestBody, "",
      &TestResult::cleanupCallResult, TestPhase::Cleanup, " in CLEANUP")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Anomaly;

      const string anomalyWhy = Random<string>();
      Anomaly anomaly;
      anomaly.why = anomalyWhy;
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).testPhase = testPhase;

      _testResult_WriteTestCaseNumberIfAnyMocked.responsibleCallResultField = expectedResponsibleCallResultField;

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
      ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
      ZEN(_consoleMock.WriteMock.CalledAsFollows(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
         expectedTestPhaseSuffix
      }));
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZEN(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
      ZEN(_consoleMock.WriteLineMock.CalledOnceWith(anomalyWhy));
      ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
   }

   TEST3X3(PrintIfFailure_Exception_PrintsExpected,
      CallResult TestResult::* expectedResponsibleCallResultField,
      TestPhase testPhase,
      const string& expectedTestPhaseSuffix,
      &TestResult::constructorCallResult, TestPhase::Constructor, " in test class constructor",
      &TestResult::startupCallResult, TestPhase::Startup, " in STARTUP",
      &TestResult::testBodyCallResult, TestPhase::TestBody, "",
      &TestResult::cleanupCallResult, TestPhase::Cleanup, " in CLEANUP")
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Exception;

      const string exceptionTypeName = Random<string>();
      const string exceptionWhatString = Random<string>();
      const char* const exceptionWhat = exceptionWhatString.c_str();
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(&exceptionTypeName, exceptionWhat);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).testPhase = testPhase;
      _testResult_WriteTestCaseNumberIfAnyMocked.
         responsibleCallResultField = expectedResponsibleCallResultField;

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
      ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
      ZEN(_consoleMock.WriteMock.CalledAsFollows(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
         expectedTestPhaseSuffix
      }));
      ZEN(_consoleMock.WriteLineColorMock.CalledAsFollows(
      {
         { testFailureNumber, Color::Red },
         { "\nUncaught Exception", Color::Red }
      }));
      ZEN(_consoleMock.WriteLineMock.CalledOnceWith(
         "  Type: " + exceptionTypeName + "\n"
         "what(): \""s + exceptionWhat + "\""));
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
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
      ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseNumber));
      ZEN(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
      ZEN(_consoleMock.WriteLineMock.CalledAsFollows(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
         "\nFailed because test took longer than -maxtestms=10 milliseconds"s
      }));
      ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
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
      //
      _testResult.WriteTestCaseNumberIfAny(&_consoleMock, testCaseNumber);
      //
      if (expectConsoleWriteLine)
      {
         ZEN(_consoleMock.WriteMock.CalledOnceWith(" test case " + to_string(testCaseNumber)));
      }
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestResult);
      EQUALIZER_THROWS_FOR_FIELD(TestResult, fullTestName, FullTestName("ClassName", "TestName", 0));

      CallResult nonDefaultConstructorCallResult;
      nonDefaultConstructorCallResult.testPhase = TestPhase::Constructor;
      EQUALIZER_THROWS_FOR_FIELD(TestResult, constructorCallResult, nonDefaultConstructorCallResult);

      CallResult nonDefaultStartupCallResult;
      nonDefaultStartupCallResult.testPhase = TestPhase::Startup;
      EQUALIZER_THROWS_FOR_FIELD(TestResult, startupCallResult, nonDefaultStartupCallResult);

      CallResult nonDefaultTestBodyCallResult;
      nonDefaultTestBodyCallResult.testPhase = TestPhase::TestBody;
      EQUALIZER_THROWS_FOR_FIELD(TestResult, testBodyCallResult, nonDefaultTestBodyCallResult);

      CallResult nonDefaultCleanupCallResult;
      nonDefaultCleanupCallResult.testPhase = TestPhase::Cleanup;
      EQUALIZER_THROWS_FOR_FIELD(TestResult, cleanupCallResult, nonDefaultCleanupCallResult);

      CallResult nonDefaultDestructorCallResult;
      nonDefaultDestructorCallResult.testPhase = TestPhase::Destructor;
      EQUALIZER_THROWS_FOR_FIELD(TestResult, destructorCallResult, nonDefaultDestructorCallResult);

      EQUALIZER_THROWS_FOR_FIELD(TestResult, responsibleCallResultField, &TestResult::constructorCallResult);
      EQUALIZER_THROWS_FOR_FIELD(TestResult, testOutcome, TestOutcome::Anomaly);
      EQUALIZER_THROWS_FOR_FIELD(TestResult, testCaseNumber, short(10));
      EQUALIZER_THROWS_FOR_FIELD(TestResult, microseconds, 20u);
   }

   RUN_TESTS(TestResultTests)
}
