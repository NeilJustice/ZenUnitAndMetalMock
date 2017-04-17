#include "pch.h"
#include "ZenUnit/TestRunners/TemplateTestClassRunner.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberForEacherExtraArgMock.h"

namespace ZenUnit
{
   TESTS(TemplateTestClassRunnerTests)
   SPEC(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   SPEC(TestClassName_ReturnsTestClassName)
   SPEC(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   SPECX(RunTests_PrintsTestClassNameAndNumberOfTests_ForEachRunsTests_PrintsTestClassResultLine_ReturnsTestClassResult)
   SPECX(PrintTestClassNameAndNumberOfTests_WritesTestClassNameVerticalBarNumberOfTests)
   SPECX(ConfirmNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsItResultToResults_ReturnsTrueIfSuccess)
   SPEC(RunTest_WritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_WriteLinesTestOutcome)
   SPEC(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   SPECEND

   class TestingTestClass
   {
   public:
      static vector<unique_ptr<Test>> GetTests()
      {
         vector<unique_ptr<Test>> tests;
         tests.emplace_back(nullptr);
         return tests;
      }
   };

   unique_ptr<TemplateTestClassRunner<TestingTestClass>> _templateTestClassRunner;
   ConsoleMock* _consoleMock;
   const char* TestClassName = "TestClassName";

   class TemplateTestClassRunnerSelfMocked : public Zen::Mock<ZenUnit::TemplateTestClassRunner<TestingTestClass>>
   {
   public:
      ZENMOCK_VOID0_CONST(PrintTestClassNameAndNumberOfTests)
      ZENMOCK_NONVOID2_CONST(bool, ConfirmNewableAndDeletableAndRegisterNXNTests, Test*, TestClassResult*)
      ZENMOCK_VOID1_CONST(PrintTestClassResultLine, const TestClassResult*)

      const ConsoleMock* consoleMock;

      using TestsMemberForEacherExtraArgMockType = MemberForEacherExtraArgMock<
         std::vector<std::unique_ptr<Test>>,
         TemplateTestClassRunner<TestingTestClass>,
         void (TemplateTestClassRunner<TestingTestClass>::*)(
            const std::unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
      const TestsMemberForEacherExtraArgMockType* testsMemberForEacherExtraArgMock;

      TemplateTestClassRunnerSelfMocked()
         : Zen::Mock<ZenUnit::TemplateTestClassRunner<TestingTestClass>>("")
      {
         _console.reset(consoleMock = new ConsoleMock);
         _testsMemberForEacherExtraArg.reset(
            testsMemberForEacherExtraArgMock = new TestsMemberForEacherExtraArgMockType);
      }
   };
   unique_ptr<TemplateTestClassRunnerSelfMocked> _templateTestClassRunnerSelfMocked;

   STARTUP
   {
      _templateTestClassRunner = make_unique<TemplateTestClassRunner<TestingTestClass>>(TestClassName);
      _templateTestClassRunner->_console.reset(_consoleMock = new ConsoleMock);
      _templateTestClassRunnerSelfMocked = make_unique<TemplateTestClassRunnerSelfMocked>();
   }

   TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   {
      TemplateTestClassRunner<TestingTestClass> templateTestClassRunner(TestClassName);
      //
      WAS_NEWED(templateTestClassRunner._console);
      WAS_NEWED(templateTestClassRunner._testsMemberForEacherExtraArg);
      ARE_EQUAL(TestClassName, templateTestClassRunner._testClassName);

      vector<unique_ptr<Test>> expectedTests;
      expectedTests.emplace_back(nullptr);
      VECTORS_EQUAL(expectedTests, templateTestClassRunner._tests);
   }

   TEST(TestClassName_ReturnsTestClassName)
   {
      const char* testClassName = _templateTestClassRunner->TestClassName();
      ARE_EQUAL(TestClassName, testClassName);
   }

   TEST(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   {
      _templateTestClassRunner->_tests.resize(3);
      TestMock* const testMockA = new TestMock;
      testMockA->NumberOfTestCasesMock.ExpectAndReturn(10);
      TestMock* const testMockB = new TestMock;
      testMockB->NumberOfTestCasesMock.ExpectAndReturn(0);
      TestMock* const testMockC = new TestMock;
      testMockC->NumberOfTestCasesMock.ExpectAndReturn(20);
      _templateTestClassRunner->_tests[0].reset(testMockA);
      _templateTestClassRunner->_tests[1].reset(testMockB);
      _templateTestClassRunner->_tests[2].reset(testMockC);
      //
      const size_t numberOfTestCases = _templateTestClassRunner->NumberOfTestCases();
      //
      ZEN(testMockA->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testMockB->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testMockC->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(30, numberOfTestCases);
   }

   TEST2X2(RunTests_PrintsTestClassNameAndNumberOfTests_ForEachRunsTests_PrintsTestClassResultLine_ReturnsTestClassResult,
      bool testClassTypeNewableAndDeletable, bool expectTestsRunForEachCall,
      false, false,
      true, true)
   {
      _templateTestClassRunnerSelfMocked->PrintTestClassNameAndNumberOfTestsMock.Expect();
      _templateTestClassRunnerSelfMocked->ConfirmNewableAndDeletableAndRegisterNXNTestsMock
         .ExpectAndReturn(testClassTypeNewableAndDeletable);
      if (expectTestsRunForEachCall)
      {
         _templateTestClassRunnerSelfMocked->testsMemberForEacherExtraArgMock->ForEachMock.Expect();
      }
      _templateTestClassRunnerSelfMocked->PrintTestClassResultLineMock.Expect();
      _templateTestClassRunnerSelfMocked->consoleMock->WriteNewlineMock.Expect();
      _templateTestClassRunnerSelfMocked->_testClassResult = TestClassResult::TestingNonDefault();
      //
      const TestClassResult testClassResult = _templateTestClassRunnerSelfMocked->RunTests();
      //
      ZEN(_templateTestClassRunnerSelfMocked->PrintTestClassNameAndNumberOfTestsMock.AssertCalledOnce());
      ZEN(_templateTestClassRunnerSelfMocked->ConfirmNewableAndDeletableAndRegisterNXNTestsMock.AssertCalledOnceWith(
          &_templateTestClassRunnerSelfMocked->_newDeleteTest, &_templateTestClassRunnerSelfMocked->_testClassResult));
      if (expectTestsRunForEachCall)
      {
         ZEN(_templateTestClassRunnerSelfMocked->testsMemberForEacherExtraArgMock->ForEachMock.AssertCalledOnceWith(
            &_templateTestClassRunnerSelfMocked->_tests,
            _templateTestClassRunnerSelfMocked.get(),
            &TemplateTestClassRunner<TestingTestClass>::RunTest,
            &_templateTestClassRunnerSelfMocked->_testClassResult));
      }
      ZEN(_templateTestClassRunnerSelfMocked->PrintTestClassResultLineMock.
         AssertCalledOnceWith(&_templateTestClassRunnerSelfMocked->_testClassResult));
      ZEN(_templateTestClassRunnerSelfMocked->consoleMock->WriteNewlineMock.AssertCalledOnce());
      ARE_EQUAL(_templateTestClassRunnerSelfMocked->_testClassResult, testClassResult);
   }

   TEST2X2(PrintTestClassNameAndNumberOfTests_WritesTestClassNameVerticalBarNumberOfTests,
      size_t numberOfTests, bool expectTestsPlural,
      0ULL, true,
      1ULL, false,
      2ULL, true,
      3ULL, true)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _templateTestClassRunner->_testClassName = TestClassName;
      _templateTestClassRunner->_tests.resize(numberOfTests);
      //
      _templateTestClassRunner->PrintTestClassNameAndNumberOfTests();
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalls(
      {
         { "@", Color::Green },
         { TestClassName, Color::Green }
      }));
      if (expectTestsPlural)
      {
         ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(String::Concat(" | ", numberOfTests, " named tests")));
      }
      else
      {
         ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(String::Concat(" | ", numberOfTests, " named test")));
      }
   }

   TEST2X2(ConfirmNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsItResultToResults_ReturnsTrueIfSuccess,
      bool expectedReturnValue, TestOutcome newDeleteTestOutcome,
      false, TestOutcome::Anomaly,
      false, TestOutcome::Exception,
      true, TestOutcome::Success)
   {
      TestMock testMock;

      TestResult testResult;
      testResult.testOutcome = newDeleteTestOutcome;
      const vector<TestResult> testResults = { testResult };
      testMock.RunMock.ExpectAndReturn(testResults);

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      const bool testClassTypeIsNewableAndDeletable = _templateTestClassRunner->
         ConfirmNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
      //
      ZEN(testMock.RunMock.AssertCalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.AssertCalledOnceWith(testResults));
      ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
   }

   TEST(RunTest_WritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_WriteLinesTestOutcome)
   {
      _templateTestClassRunnerSelfMocked->consoleMock->WriteColorMock.Expect();
      _templateTestClassRunnerSelfMocked->consoleMock->WriteMock.Expect();

      TestMock* testMock = new TestMock;
      const char* TestName = "TestName";
      testMock->NameMock.ExpectAndReturn(TestName);
      testMock->PrintPostTestNameMessageMock.Expect();
      TestResult test0;
      test0.fullName = FullName("", "Test0");
      const vector<TestResult> TestResults = { test0, TestResult() };
      testMock->RunMock.ExpectAndReturn(TestResults);
      testMock->PrintPostTestCompletionMessageMock.Expect();
      const unique_ptr<Test> test(testMock);

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      _templateTestClassRunnerSelfMocked->RunTest(test, &testClassResultMock);
      //
      ZEN(_templateTestClassRunnerSelfMocked->consoleMock->WriteColorMock.AssertCalledOnceWith("|", Color::Green));
      ZEN(_templateTestClassRunnerSelfMocked->consoleMock->WriteMock.AssertCalledOnceWith(TestName));
      ZEN(testMock->NameMock.AssertCalledOnce());
      ZEN(testMock->PrintPostTestNameMessageMock.AssertCalledOnceWith(_templateTestClassRunnerSelfMocked->_console.get()));
      ZEN(testMock->RunMock.AssertCalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.AssertCalledOnceWith(TestResults));
      ZEN(testMock->PrintPostTestCompletionMessageMock.AssertCalledOnceWith(
         _templateTestClassRunnerSelfMocked->_console.get(), test0));
   }

   TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintResultLineMock.Expect();
      //
      _templateTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
      //
      ZEN(testClassResultMock.PrintResultLineMock.AssertCalledOnceWith(_consoleMock));
   }

   }; RUN(TemplateTestClassRunnerTests)
}
