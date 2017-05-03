#include "pch.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestFailureNumbererMock.h"

namespace ZenUnit
{
   TESTS(TestResultTests)
   SPEC(DefaultConstructor_SetsFieldsTo0)
   SPECX(ConstructorFail_ReturnsExpectedTestResult)
   SPECX(StartupFail_ReturnsExpectedTestResult)
   SPEC(CtorDtorSuccess_ReturnsExpectedTestResult);
   SPECX(SixArgConstructor_SetsFields)
   SPECX(PrintOKIfTestPassed_PrintsOKIfTestPassed)
   SPEC(PrintIfFailure_Success_PrintsNothing)
   SPECX(PrintIfFailure_Anomaly_PrintsExpected)
   SPECX(PrintIfFailure_Exception_PrintsExpected)
   SPEC(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
   SPEC(PrintIfFailure_InvalidOutcome_Throws)
   SPECX(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseIndexPlus1IfTestCaseIndexNotMaxValue)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TestResult _testResult;
   CallResult ConstructorCallResult;
   CallResult StartupCallResult;
   CallResult DestructorCallResult;
   ConsoleMock _consoleMock;
   TestFailureNumbererMock _testFailureNumbererMock;
   const ClassNameTestName FullNameValue = ClassNameTestName("ClassName", "TestClassName");
   const unsigned ExpectedMilliseconds = 1 + 2 + 3 + 4 + 5;
   ZENMOCK_NONVOID0_STATIC(ZenUnitArgs, ZenUnit::TestRunner, GetArgs)

   struct TestResult_WriteTestCaseNumberIfAnyMocked : public Zen::Mock<TestResult>
   {
      ZENMOCK_VOID2_CONST(WriteTestCaseNumberIfAny, const Console*, unsigned short)
   } _testResult_WriteTestCaseNumberIfAnyMocked;

   STARTUP
   {
      ConstructorCallResult = CallResult(TestPhase::Constructor);
      ConstructorCallResult.milliseconds = 1;
      StartupCallResult = CallResult(TestPhase::Startup);
      StartupCallResult.milliseconds = 2;
      DestructorCallResult = CallResult(TestPhase::Destructor);
      DestructorCallResult.milliseconds = 3;
      _testResult.classNameTestName = FullNameValue;
   }

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const TestResult defaultTestResult;
      TestResult expectedDefaultTestResult;
      expectedDefaultTestResult.classNameTestName = ClassNameTestName();
      expectedDefaultTestResult.constructorCallResult = CallResult();
      expectedDefaultTestResult.startupCallResult = CallResult();
      expectedDefaultTestResult.testBodyCallResult = CallResult();
      expectedDefaultTestResult.cleanupCallResult = CallResult();
      expectedDefaultTestResult.destructorCallResult = CallResult();
      expectedDefaultTestResult.responsibleCallResultField = nullptr;
      expectedDefaultTestResult.testOutcome = TestOutcome::Unset;
      expectedDefaultTestResult.testCaseIndex = numeric_limits<unsigned short>::max();
      expectedDefaultTestResult.milliseconds = 0;
      ARE_EQUAL(expectedDefaultTestResult, defaultTestResult);
   }

   TEST2X2(ConstructorFail_ReturnsExpectedTestResult,
      TestOutcome constructorOutcome, TestOutcome expectedTestResultOutcome,
      TestOutcome::Anomaly, TestOutcome::Anomaly,
      TestOutcome::Exception, TestOutcome::Exception)
   {
      ConstructorCallResult.testOutcome = constructorOutcome;
      //
      const TestResult constructorFailTestResult =
         TestResult::ConstructorFail(FullNameValue, ConstructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.classNameTestName = FullNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.milliseconds = ConstructorCallResult.milliseconds;
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
         FullNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.classNameTestName = FullNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.startupCallResult = StartupCallResult;
      expectedTestResult.destructorCallResult = DestructorCallResult;
      expectedTestResult.responsibleCallResultField = &TestResult::startupCallResult;
      expectedTestResult.testOutcome = expectedTestResultOutcome;
      expectedTestResult.milliseconds =
         ConstructorCallResult.milliseconds + StartupCallResult.milliseconds + DestructorCallResult.milliseconds;
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(CtorDtorSuccess_ReturnsExpectedTestResult)
   {
      CallResult constructorCallResult(TestPhase::Constructor);
      constructorCallResult.milliseconds = 10;
      CallResult destructorCallResult(TestPhase::Destructor);
      destructorCallResult.milliseconds = 20;
      //
      const TestResult testResult = TestResult::CtorDtorSuccess(
         FullNameValue, constructorCallResult, destructorCallResult);
      //
      TestResult expectedTestResult;
      expectedTestResult.classNameTestName = FullNameValue;
      expectedTestResult.testOutcome = TestOutcome::Success;
      expectedTestResult.constructorCallResult = constructorCallResult;
      expectedTestResult.destructorCallResult = destructorCallResult;
      expectedTestResult.milliseconds = constructorCallResult.milliseconds + destructorCallResult.milliseconds;
      expectedTestResult.responsibleCallResultField = nullptr;
      ARE_EQUAL(expectedTestResult, testResult);
   }

   TEST6X6(SixArgConstructor_SetsFields,
      TestOutcome testBodyOutcome,
      TestOutcome cleanupOutcome,
      unsigned maxtestmilliseconds,
      int relativeMilliseconds,
      TestOutcome expectedOverallOutcome,
      CallResult TestResult::* expectedResponsibleCallResultField,
      TestOutcome::Success, TestOutcome::Success, 0, 0, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, 0, 1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, ExpectedMilliseconds, -1, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, ExpectedMilliseconds, 0, TestOutcome::Success, nullptr,
      TestOutcome::Success, TestOutcome::Success, ExpectedMilliseconds, 1, TestOutcome::SuccessButPastDeadline, nullptr,
      TestOutcome::Success, TestOutcome::Success, ExpectedMilliseconds, 2, TestOutcome::SuccessButPastDeadline, nullptr,
      TestOutcome::Exception, TestOutcome::Success, ExpectedMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
      TestOutcome::Exception, TestOutcome::Exception, ExpectedMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
      TestOutcome::Exception, TestOutcome::Anomaly, ExpectedMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
      TestOutcome::Success, TestOutcome::Exception, ExpectedMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,
      TestOutcome::Anomaly, TestOutcome::Exception, ExpectedMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,
      TestOutcome::Anomaly, TestOutcome::Success, ExpectedMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult,
      TestOutcome::Success, TestOutcome::Anomaly, ExpectedMilliseconds, 1, TestOutcome::Anomaly, &TestResult::cleanupCallResult,
      TestOutcome::Anomaly, TestOutcome::Anomaly, ExpectedMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult)
   {
      CallResult testBodyCallResult(TestPhase::TestBody);
      testBodyCallResult.testOutcome = testBodyOutcome;
      testBodyCallResult.milliseconds = 4ll;
      CallResult cleanupCallResult(TestPhase::Cleanup);
      cleanupCallResult.testOutcome = cleanupOutcome;
      cleanupCallResult.milliseconds = 5 + relativeMilliseconds;

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.maxtestmilliseconds = maxtestmilliseconds;
      if (expectedOverallOutcome == TestOutcome::Success ||
          expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgs_ZenMock.ExpectAndReturn(zenUnitArgs);
      }
      const function<ZenUnitArgs()> boundMockGetArgs = ZENBIND0(GetArgs_ZenMock);
      //
      const TestResult testResult(
         FullNameValue,
         ConstructorCallResult,
         StartupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         DestructorCallResult,
         boundMockGetArgs);
      //
      if (expectedOverallOutcome == TestOutcome::Success ||
          expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
      {
         GetArgs_ZenMock.AssertCalledOnce();
      }
      TestResult expectedTestResult;
      expectedTestResult.classNameTestName = FullNameValue;
      expectedTestResult.constructorCallResult = ConstructorCallResult;
      expectedTestResult.startupCallResult = StartupCallResult;
      expectedTestResult.testBodyCallResult = testBodyCallResult;
      expectedTestResult.cleanupCallResult = cleanupCallResult;
      expectedTestResult.destructorCallResult = DestructorCallResult;
      expectedTestResult.responsibleCallResultField = expectedResponsibleCallResultField;
      expectedTestResult.testOutcome = expectedOverallOutcome;
      expectedTestResult.testCaseIndex = numeric_limits<unsigned short>::max();
      expectedTestResult.milliseconds = ExpectedMilliseconds + relativeMilliseconds;
      ARE_EQUAL(expectedTestResult, testResult);
   }

   TEST2X2(PrintOKIfTestPassed_PrintsOKIfTestPassed,
      TestOutcome testOutcome, bool expectWriteLineOK,
      TestOutcome::Success, true,
      TestOutcome::Anomaly, false,
      TestOutcome::Exception, false,
      TestOutcome::SuccessButPastDeadline, false,
      TestOutcome::Unset, false)
   {
      _testResult.testOutcome = testOutcome;
      if (expectWriteLineOK)
      {
         _consoleMock.WriteLineColorMock.Expect();
      }
      //
      _testResult.PrintOKIfTestPassed(&_consoleMock);
      //
      if (expectWriteLineOK)
      {
         ZEN(_consoleMock.WriteLineColorMock.AssertCalledOnceWith("OK", Color::White));
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
      _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName = ClassNameTestName("TestClass", "Test");
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Anomaly;

      const string AnomalyWhy = "AnomalyWhy";
      Anomaly anomaly;
      anomaly.why = AnomalyWhy;
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(anomaly);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).testPhase = testPhase;

      _testResult_WriteTestCaseNumberIfAnyMocked.responsibleCallResultField = expectedResponsibleCallResultField;

      const string TestFailureNumber = "<10>";
      _testFailureNumbererMock.NextMock.ExpectAndReturn(TestFailureNumber);

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewlineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZEN(_testFailureNumbererMock.NextMock.AssertCalledOnce());
      ZEN(_consoleMock.WriteMock.AssertCalls(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName.TestsAndTestLines(),
         expectedTestPhaseSuffix
      }));
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         AssertCalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
      ZEN(_consoleMock.WriteLineMock.AssertCalls(
      {
         TestFailureNumber,
         AnomalyWhy
      }));
      ZEN(_consoleMock.WriteNewlineMock.AssertCalledOnce());
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
      _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName = ClassNameTestName("TestClass", "Test");
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Exception;

      const string ExceptionTypeName = "ExceptionType";
      const char* const ExceptionWhat = "ExceptionWhat";
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(&ExceptionTypeName, ExceptionWhat);
      (_testResult_WriteTestCaseNumberIfAnyMocked.*
         expectedResponsibleCallResultField).testPhase = testPhase;
      _testResult_WriteTestCaseNumberIfAnyMocked.
         responsibleCallResultField = expectedResponsibleCallResultField;

      const string TestFailureNumber = "<20>";
      _testFailureNumbererMock.NextMock.ExpectAndReturn(TestFailureNumber);

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

      _consoleMock.WriteMock.Expect();
      _consoleMock.WriteLineColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewlineMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZEN(_testFailureNumbererMock.NextMock.AssertCalledOnce());
      ZEN(_consoleMock.WriteMock.AssertCalls(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName.TestsAndTestLines(),
         expectedTestPhaseSuffix
      }));
      ZEN(_consoleMock.WriteLineColorMock.AssertCalledOnceWith("\nUncaught Exception", Color::Red));
      ZEN(_consoleMock.WriteLineMock.AssertCalls(
      {
         TestFailureNumber,
         "  Type: " + ExceptionTypeName + "\n"
         "what(): \"" + ExceptionWhat + "\""
      }));
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         AssertCalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
      ZEN(_consoleMock.WriteNewlineMock.AssertCalledOnce());
   }

   TEST(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName = ClassNameTestName("TestClass", "Test");
      _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::SuccessButPastDeadline;
      _testResult_WriteTestCaseNumberIfAnyMocked.milliseconds = 10;

      const string TestFailureNumber = "<30>";
      _testFailureNumbererMock.NextMock.ExpectAndReturn(TestFailureNumber);

      _consoleMock.WriteLineMock.Expect();
      _consoleMock.WriteNewlineMock.Expect();

      _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
      _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();
      //
      _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
      //
      ZEN(_testFailureNumbererMock.NextMock.AssertCalledOnce());
      ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
         AssertCalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
      ZEN(_consoleMock.WriteLineMock.AssertCalls(
      {
         TestFailureNumber,
         _testResult_WriteTestCaseNumberIfAnyMocked.classNameTestName.TestsAndTestLines(),
         "\nFailed because test took longer than -maxtestms= (10 ms)"s
      }));
      ZEN(_consoleMock.WriteNewlineMock.AssertCalledOnce());
   }

   TEST(PrintIfFailure_InvalidOutcome_Throws)
   {
      _testResult.testOutcome = TestOutcome::Unset;
      THROWS(_testResult.PrintIfFailure(nullptr, nullptr), logic_error,
         R"(assert_true(testOutcome == TestOutcome::SuccessButPastDeadline) failed in PrintIfFailure()
File.cpp(1))");
   }

   TEST3X3(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseIndexPlus1IfTestCaseIndexNotMaxValue,
      unsigned short testCaseIndex, bool expectConsoleWriteLine, unsigned short expectedTestCaseNumberWritten,
      static_cast<unsigned short>(numeric_limits<unsigned short>::max()), false, NA<unsigned short>(),
      static_cast<unsigned short>(0), true, static_cast<unsigned short>(1),
      static_cast<unsigned short>(1), true, static_cast<unsigned short>(2),
      static_cast<unsigned short>(2), true, static_cast<unsigned short>(3))
   {
      if (expectConsoleWriteLine)
      {
         _consoleMock.WriteMock.Expect();
      }
      //
      _testResult.WriteTestCaseNumberIfAny(&_consoleMock, testCaseIndex);
      //
      if (expectConsoleWriteLine)
      {
         ZEN(_consoleMock.WriteMock.AssertCalledOnceWith(
            " test case " + to_string(expectedTestCaseNumberWritten)));
      }
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(TestResult);
      EQUALIZER_THROWS(TestResult, classNameTestName, ClassNameTestName("ClassName", "TestName"));

      CallResult nonDefaultConstructorCallResult;
      nonDefaultConstructorCallResult.testPhase = TestPhase::Constructor;
      EQUALIZER_THROWS(TestResult, constructorCallResult, nonDefaultConstructorCallResult);

      CallResult nonDefaultStartupCallResult;
      nonDefaultStartupCallResult.testPhase = TestPhase::Startup;
      EQUALIZER_THROWS(TestResult, startupCallResult, nonDefaultStartupCallResult);

      CallResult nonDefaultTestBodyCallResult;
      nonDefaultTestBodyCallResult.testPhase = TestPhase::TestBody;
      EQUALIZER_THROWS(TestResult, testBodyCallResult, nonDefaultTestBodyCallResult);

      CallResult nonDefaultCleanupCallResult;
      nonDefaultCleanupCallResult.testPhase = TestPhase::Cleanup;
      EQUALIZER_THROWS(TestResult, cleanupCallResult, nonDefaultCleanupCallResult);

      CallResult nonDefaultDestructorCallResult;
      nonDefaultDestructorCallResult.testPhase = TestPhase::Destructor;
      EQUALIZER_THROWS(TestResult, destructorCallResult, nonDefaultDestructorCallResult);

      EQUALIZER_THROWS(TestResult, responsibleCallResultField, &TestResult::constructorCallResult);
      EQUALIZER_THROWS(TestResult, testOutcome, TestOutcome::Anomaly);
      EQUALIZER_THROWS(TestResult, testCaseIndex, short(10));
      EQUALIZER_THROWS(TestResult, milliseconds, 20u);
   }

   }; RUN(TestResultTests)
}
