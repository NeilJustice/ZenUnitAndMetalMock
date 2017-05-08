#include "pch.h"
#include "ZenUnit/TestRunners/SpecificTestClassRunner.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberForEacherExtraArgMock.h"

namespace ZenUnit
{
   TESTS(SpecificTestClassRunnerTests)
   SPEC(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   SPEC(TestClassNameForSorting_ReturnsTestClassName)
   SPEC(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   SPECX(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ForEachRunsTests_PrintsTestClassResultLine_ReturnsTestClassResult)
   SPECX(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests)
   SPECX(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsItResultToResults_ReturnsTrueIfSuccess)
   SPEC(RunTest_WritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_WriteLinesTestOutcome)
   SPEC(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   SPECEND

   class TestingTestClass
   {
   public:
      static vector<unique_ptr<Test>> GetTests(const char*)
      {
         vector<unique_ptr<Test>> tests;
         // emplace one Test pointer to make tests vector non-default sized
         tests.emplace_back(nullptr);
         return tests;
      }
   };

   unique_ptr<SpecificTestClassRunner<TestingTestClass>> _specificTestClassRunner;
   ConsoleMock* _consoleMock;
   const char* TestClassName = "TestClassName";

   class SpecificTestClassRunnerSelfMocked : public Zen::Mock<ZenUnit::SpecificTestClassRunner<TestingTestClass>>
   {
   public:
      ZENMOCK_VOID0_CONST(PrintTestClassNameAndNumberOfNamedTests)
      ZENMOCK_NONVOID2_CONST(bool, ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests, Test*, TestClassResult*)
      ZENMOCK_VOID1_CONST(PrintTestClassResultLine, const TestClassResult*)

      const ConsoleMock* consoleMock;

      using TestsMemberForEacherExtraArgMockType = MemberForEacherExtraArgMock<
         std::vector<std::unique_ptr<Test>>,
         SpecificTestClassRunner<TestingTestClass>,
         void (SpecificTestClassRunner<TestingTestClass>::*)(
            const std::unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
      const TestsMemberForEacherExtraArgMockType* testsMemberForEacherExtraArgMock;

      SpecificTestClassRunnerSelfMocked()
         : Zen::Mock<ZenUnit::SpecificTestClassRunner<TestingTestClass>>("")
      {
         _console.reset(consoleMock = new ConsoleMock);
         _testsMemberForEacherExtraArg.reset(
            testsMemberForEacherExtraArgMock = new TestsMemberForEacherExtraArgMockType);
      }
   };
   unique_ptr<SpecificTestClassRunnerSelfMocked> _specificTestClassRunnerSelfMocked;

   STARTUP
   {
      _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(TestClassName);
      _specificTestClassRunner->_console.reset(_consoleMock = new ConsoleMock);
      _specificTestClassRunnerSelfMocked = make_unique<SpecificTestClassRunnerSelfMocked>();
   }

   TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   {
      SpecificTestClassRunner<TestingTestClass> templateTestClassRunner(TestClassName);
      //
      WAS_NEWED(templateTestClassRunner._console);
      WAS_NEWED(templateTestClassRunner._testsMemberForEacherExtraArg);
      ARE_EQUAL(TestClassName, templateTestClassRunner._testClassName);

      vector<unique_ptr<Test>> expectedTests;
      expectedTests.emplace_back(nullptr);
      VECTORS_EQUAL(expectedTests, templateTestClassRunner._tests);
   }

   TEST(TestClassNameForSorting_ReturnsTestClassName)
   {
      const char* testClassName = _specificTestClassRunner->TestClassNameForSorting();
      ARE_EQUAL(TestClassName, testClassName);
   }

   TEST(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   {
      _specificTestClassRunner->_tests.resize(3);
      TestMock* const testMockA = new TestMock;
      testMockA->NumberOfTestCasesMock.ExpectAndReturn(10);
      TestMock* const testMockB = new TestMock;
      testMockB->NumberOfTestCasesMock.ExpectAndReturn(0);
      TestMock* const testMockC = new TestMock;
      testMockC->NumberOfTestCasesMock.ExpectAndReturn(20);
      _specificTestClassRunner->_tests[0].reset(testMockA);
      _specificTestClassRunner->_tests[1].reset(testMockB);
      _specificTestClassRunner->_tests[2].reset(testMockC);
      //
      const size_t numberOfTestCases = _specificTestClassRunner->NumberOfTestCases();
      //
      ZEN(testMockA->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testMockB->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testMockC->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(30, numberOfTestCases);
   }

   TEST2X2(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ForEachRunsTests_PrintsTestClassResultLine_ReturnsTestClassResult,
      bool testClassTypeNewableAndDeletable, bool expectTestsRunForEachCall,
      false, false,
      true, true)
   {
      _specificTestClassRunnerSelfMocked->PrintTestClassNameAndNumberOfNamedTestsMock.Expect();
      _specificTestClassRunnerSelfMocked->ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock
         .ExpectAndReturn(testClassTypeNewableAndDeletable);
      if (expectTestsRunForEachCall)
      {
         _specificTestClassRunnerSelfMocked->testsMemberForEacherExtraArgMock->ForEachMock.Expect();
      }
      _specificTestClassRunnerSelfMocked->PrintTestClassResultLineMock.Expect();
      _specificTestClassRunnerSelfMocked->consoleMock->WriteNewlineMock.Expect();
      _specificTestClassRunnerSelfMocked->_testClassResult = TestClassResult::TestingNonDefault();
      //
      const TestClassResult testClassResult = _specificTestClassRunnerSelfMocked->RunTests();
      //
      ZEN(_specificTestClassRunnerSelfMocked->PrintTestClassNameAndNumberOfNamedTestsMock.AssertCalledOnce());
      ZEN(_specificTestClassRunnerSelfMocked->ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock.AssertCalledOnceWith(
          &_specificTestClassRunnerSelfMocked->_newDeleteTest, &_specificTestClassRunnerSelfMocked->_testClassResult));
      if (expectTestsRunForEachCall)
      {
         ZEN(_specificTestClassRunnerSelfMocked->testsMemberForEacherExtraArgMock->ForEachMock.AssertCalledOnceWith(
            &_specificTestClassRunnerSelfMocked->_tests,
            _specificTestClassRunnerSelfMocked.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunnerSelfMocked->_testClassResult));
      }
      ZEN(_specificTestClassRunnerSelfMocked->PrintTestClassResultLineMock.
         AssertCalledOnceWith(&_specificTestClassRunnerSelfMocked->_testClassResult));
      ZEN(_specificTestClassRunnerSelfMocked->consoleMock->WriteNewlineMock.AssertCalledOnce());
      ARE_EQUAL(_specificTestClassRunnerSelfMocked->_testClassResult, testClassResult);
   }

   TEST2X2(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests,
      size_t numberOfTests, bool expectTestsPlural,
      0ull, true,
      1ull, false,
      2ull, true,
      3ull, true)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _specificTestClassRunner->_testClassName = TestClassName;
      _specificTestClassRunner->_tests.resize(numberOfTests);
      //
      _specificTestClassRunner->PrintTestClassNameAndNumberOfNamedTests();
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

   TEST3X3(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsItResultToResults_ReturnsTrueIfSuccess,
      bool expectedReturnValue, TestOutcome newDeleteTestOutcome, bool expectedWriteLineTrue,
      false, TestOutcome::Anomaly, false,
      false, TestOutcome::Exception, false,
      true, TestOutcome::Success, true)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      if (expectedWriteLineTrue)
      {
         _consoleMock->WriteLineMock.Expect();
      }
      TestMock testMock;

      TestResult testResult;
      testResult.testOutcome = newDeleteTestOutcome;
      const vector<TestResult> testResults = { testResult };
      testMock.RunMock.ExpectAndReturn(testResults);

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      const bool testClassTypeIsNewableAndDeletable = _specificTestClassRunner->
         ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalledOnceWith("|", Color::Green));
      ZEN(_consoleMock->WriteMock.AssertCalledOnceWith("TestClassIsNewableAndDeletable -> "));
      if (expectedWriteLineTrue)
      {
         ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("True"));
      }
      ZEN(testMock.RunMock.AssertCalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.AssertCalledOnceWith(testResults));
      ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
   }

   TEST(RunTest_WritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_WriteLinesTestOutcome)
   {
      _specificTestClassRunnerSelfMocked->consoleMock->WriteColorMock.Expect();
      _specificTestClassRunnerSelfMocked->consoleMock->WriteMock.Expect();

      TestMock* testMock = new TestMock;
      const char* TestName = "TestName";
      testMock->NameMock.ExpectAndReturn(TestName);
      testMock->PrintPostTestNameMessageMock.Expect();
      TestResult test0;
      test0.fullTestName = FullTestName("", "Test0", 0);
      const vector<TestResult> TestResults = { test0, TestResult() };
      testMock->RunMock.ExpectAndReturn(TestResults);
      testMock->PrintPostTestCompletionMessageMock.Expect();
      const unique_ptr<Test> test(testMock);

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      _specificTestClassRunnerSelfMocked->RunTest(test, &testClassResultMock);
      //
      ZEN(_specificTestClassRunnerSelfMocked->consoleMock->WriteColorMock.AssertCalledOnceWith("|", Color::Green));
      ZEN(_specificTestClassRunnerSelfMocked->consoleMock->WriteMock.AssertCalledOnceWith(TestName));
      ZEN(testMock->NameMock.AssertCalledOnce());
      ZEN(testMock->PrintPostTestNameMessageMock.AssertCalledOnceWith(_specificTestClassRunnerSelfMocked->_console.get()));
      ZEN(testMock->RunMock.AssertCalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.AssertCalledOnceWith(TestResults));
      ZEN(testMock->PrintPostTestCompletionMessageMock.AssertCalledOnceWith(
         _specificTestClassRunnerSelfMocked->_console.get(), test0));
   }

   TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintResultLineMock.Expect();
      //
      _specificTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
      //
      ZEN(testClassResultMock.PrintResultLineMock.AssertCalledOnceWith(_consoleMock));
   }

   }; RUN(SpecificTestClassRunnerTests)
}
