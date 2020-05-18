#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/ZenMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/ZenMock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/Components/Tests/ZenMock/TestMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TwoArgAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TwoArgMemberForEacherMock.h"
#include "ZenUnitTestUtils/Equalizers/TestNameFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(SpecificTestClassRunnerTests)
   AFACT(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   AFACT(TestClassName_ReturnsTestClassName)
   AFACT(HasTestThatMatchesTestNameFilter_TestNameFilterTestNamePatternIsEmpty_ReturnsTrue)
   AFACT(HasTestThatMatchesTestNameFilter_TestNameFilterTestNamePatternIsNotEmpty_ReturnsTrueIfTestNameFilterMatchesTestNameReturnsTrue)
   AFACT(TestNameFilterMatchesTestName_ReturnsTrueIfTestNameFilterMatchesTestName)
   AFACT(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   FACTS(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ConfirmsTestClassNewableAndDeletable_RunsTests_PrintsAndReturnsTestClassResult)
   FACTS(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests)
   FACTS(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests)
   FACTS(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable)
   AFACT(RunTest_TestNameFiltersAreNonEmpty_NoneOfTheTestNameFiltersMatchTheTestName_DoesNotRunTest)
   FACTS(RunTest_TestNameFiltersAreEmptyOrIfNotEmptyATestNameFilterMatchesTheTestName_RunsTest)
   AFACT(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   EVIDENCE

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
   ConsoleMock* _protected_consoleMock = nullptr;
   const string _testClassName = ZenUnit::Random<string>();

   using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
      unique_ptr<Test>, SpecificTestClassRunner<TestingTestClass>,
      void (SpecificTestClassRunner<TestingTestClass>::*)(
         const unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
   TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock = nullptr;
   VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>* _voidZeroArgMemberFunctionCallerMock = nullptr;
   NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>* _nonVoidTwoArgFunctionCallerMock = nullptr;
   VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>* _voidOneArgMemberFunctionCallerMock = nullptr;

   using TwoArgTestAnyerMockType = TwoArgAnyerMock<
      const std::vector<std::unique_ptr<Test>>,
      bool(*)(const std::unique_ptr<Test>&, const TestNameFilter&),
      const TestNameFilter&>;
   TwoArgTestAnyerMockType* _twoArgTestAnyerMock = nullptr;

   using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
      std::vector<TestNameFilter>, TestClassRunner,
      bool(TestClassRunner::*)(const TestNameFilter&, const char*) const, const char*>;
   TwoArgMemberAnyerMockType* _protected_twoArgMemberAnyerMock = nullptr;

   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)

   STARTUP
   {
      _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
      _specificTestClassRunner->_protected_console.reset(_protected_consoleMock = new ConsoleMock);
      _specificTestClassRunner->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_ZENMOCK_OBJECT(GetZenUnitArgsMock);
      _specificTestClassRunner->_twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      _specificTestClassRunner->_voidZeroArgMemberFunctionCaller.reset(
         _voidZeroArgMemberFunctionCallerMock =
         new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
      _specificTestClassRunner->_nonVoidTwoArgFunctionCaller.reset(
         _nonVoidTwoArgFunctionCallerMock =
         new NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>);
      _specificTestClassRunner->_voidOneArgFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock =
         new VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>);
      _specificTestClassRunner->_twoArgTestAnyer.reset(_twoArgTestAnyerMock = new TwoArgTestAnyerMockType);
      _specificTestClassRunner->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_ZENMOCK_OBJECT(GetZenUnitArgsMock);
      _specificTestClassRunner->_protected_twoArgMemberAnyer.reset(_protected_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
   }

   TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   {
      SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(_testClassName.c_str());
      //
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._protected_console);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgMemberForEacher);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidZeroArgMemberFunctionCaller);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgTestAnyer);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._nonVoidTwoArgFunctionCaller);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidOneArgFunctionCaller);
      ARE_EQUAL(_testClassName.c_str(), specificTestClassRunner._testClassName);
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, specificTestClassRunner._call_ZenUnitTestRunner_GetZenUnitArgs);

      vector<unique_ptr<Test>> expectedTests;
      expectedTests.emplace_back(nullptr);
      VECTORS_EQUAL(expectedTests, specificTestClassRunner._tests);
   }

   TEST(TestClassName_ReturnsTestClassName)
   {
      const char* const testClassName = _specificTestClassRunner->TestClassName();
      ARE_EQUAL(_testClassName.c_str(), testClassName);
   }

   TEST(HasTestThatMatchesTestNameFilter_TestNameFilterTestNamePatternIsEmpty_ReturnsTrue)
   {
      const TestNameFilter testNameFilterWithEmptyTestName;
      IS_EMPTY(testNameFilterWithEmptyTestName.testNamePattern);
      //
      const bool hasTestThatMatchesTestNameFilter = _specificTestClassRunner->HasTestThatMatchesTestNameFilter(testNameFilterWithEmptyTestName);
      //
      IS_TRUE(hasTestThatMatchesTestNameFilter);
   }

   TEST(HasTestThatMatchesTestNameFilter_TestNameFilterTestNamePatternIsNotEmpty_ReturnsTrueIfTestNameFilterMatchesTestNameReturnsTrue)
   {
      const bool twoArgAnyerReturnValue = _twoArgTestAnyerMock->TwoArgAnyMock.ReturnRandom();
      const TestNameFilter testNameFilter = ZenUnit::Random<TestNameFilter>();
      //
      const bool hasTestThatMatchesTestNameFilter = _specificTestClassRunner->HasTestThatMatchesTestNameFilter(testNameFilter);
      //
      ZENMOCK(_twoArgTestAnyerMock->TwoArgAnyMock.CalledOnceWith(
         &_specificTestClassRunner->_tests, SpecificTestClassRunner<TestingTestClass>::TestNameFilterMatchesTestName, testNameFilter));
      ARE_EQUAL(twoArgAnyerReturnValue, hasTestThatMatchesTestNameFilter);
   }

   TEST(TestNameFilterMatchesTestName_ReturnsTrueIfTestNameFilterMatchesTestName)
   {
      TestMock* testMock = new TestMock;
      const string testName = ZenUnit::Random<string>();
      testMock->NameMock.Return(testName.c_str());
      unique_ptr<Test> test(testMock);

      TestNameFilterMock testNameFilterMock;
      const bool testNameFilterMatchesTestName = testNameFilterMock.MatchesTestNameMock.ReturnRandom();
      //
      const bool returnedTestNameFilterMatchesTestName = _specificTestClassRunner->TestNameFilterMatchesTestName(test, testNameFilterMock);
      //
      ZENMOCK(testMock->NameMock.CalledOnce());
      ZENMOCK(testNameFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
      ARE_EQUAL(testNameFilterMatchesTestName, returnedTestNameFilterMatchesTestName);
   }

   TEST(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   {
      _specificTestClassRunner->_tests.resize(3);
      TestMock* const testMockA = new TestMock;
      testMockA->NumberOfTestCasesMock.Return(10);
      TestMock* const testMockB = new TestMock;
      testMockB->NumberOfTestCasesMock.Return(0);
      TestMock* const testMockC = new TestMock;
      testMockC->NumberOfTestCasesMock.Return(20);
      _specificTestClassRunner->_tests[0].reset(testMockA);
      _specificTestClassRunner->_tests[1].reset(testMockB);
      _specificTestClassRunner->_tests[2].reset(testMockC);
      //
      const size_t numberOfTestCases = _specificTestClassRunner->NumberOfTestCases();
      //
      ZENMOCK(testMockA->NumberOfTestCasesMock.CalledOnce());
      ZENMOCK(testMockB->NumberOfTestCasesMock.CalledOnce());
      ZENMOCK(testMockC->NumberOfTestCasesMock.CalledOnce());
      ARE_EQUAL(30, numberOfTestCases);
   }

   TEST2X2(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ConfirmsTestClassNewableAndDeletable_RunsTests_PrintsAndReturnsTestClassResult,
      bool testClassTypeNewableAndDeletable, bool expectDoRunTestsCall,
      false, false,
      true, true)
   {
      _voidZeroArgMemberFunctionCallerMock->ConstCallMock.Expect();
      _nonVoidTwoArgFunctionCallerMock->ConstCallMock.Return(testClassTypeNewableAndDeletable);
      if (expectDoRunTestsCall)
      {
         _voidZeroArgMemberFunctionCallerMock->NonConstCallMock.Expect();
      }
      _voidOneArgMemberFunctionCallerMock->ConstCallMock.Expect();
      _protected_consoleMock->WriteNewLineMock.Expect();
      _specificTestClassRunner->_testClassResult = TestClassResult::TestingNonDefault();
      //
      const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
      //
      ZENMOCK(_voidZeroArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassNameAndNumberOfNamedTests));
      ZENMOCK(_nonVoidTwoArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
         &_specificTestClassRunner->_newableDeletableTest, &_specificTestClassRunner->_testClassResult));
      if (expectDoRunTestsCall)
      {
         ZENMOCK(_voidZeroArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
            _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
      }
      ZENMOCK(_voidOneArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassResultLine,
         &_specificTestClassRunner->_testClassResult));
      ZENMOCK(_protected_consoleMock->WriteNewLineMock.CalledOnce());
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
      ARE_EQUAL(TestClassResult(), _specificTestClassRunner->_testClassResult);
   }

   TEST2X2(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests,
      bool randomTestOrdering, bool expectRandomForEach,
      false, false,
      true, true)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.randomTestOrdering = randomTestOrdering;
      zenUnitArgs.randomSeed = Random<unsigned>();
      GetZenUnitArgsMock.Return(zenUnitArgs);
      if (expectRandomForEach)
      {
         _twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.Expect();
      }
      else
      {
         _twoArgMemberForEacherMock->TwoArgMemberForEachMock.Expect();
      }
      //
      _specificTestClassRunner->DoRunTests();
      //
      ZENMOCK(GetZenUnitArgsMock.CalledOnce());
      if (expectRandomForEach)
      {
         ZENMOCK(_twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult,
            zenUnitArgs.randomSeed));
      }
      else
      {
         ZENMOCK(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult));
      }
   }

   TEST2X2(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests,
      size_t numberOfTests, bool expectTestsPlural,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true,
      size_t(3), true)
   {
      _protected_consoleMock->WriteColorMock.Expect();
      _protected_consoleMock->WriteLineMock.Expect();
      _specificTestClassRunner->_testClassName = _testClassName.c_str();
      _specificTestClassRunner->_tests.resize(numberOfTests);
      //
      _specificTestClassRunner->PrintTestClassNameAndNumberOfNamedTests();
      //
      ZENMOCK(_protected_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "@", Color::Green },
            { _testClassName.c_str(), Color::Green }
         }));
      if (expectTestsPlural)
      {
         ZENMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(
            String::Concat(" | Running ", numberOfTests, " tests")));
      }
      else
      {
         ZENMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(
            String::Concat(" | Running ", numberOfTests, " test")));
      }
   }

   TEST3X3(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable,
      bool expectedReturnValue, TestOutcome newableDeletableTestOutcome, bool expectWriteLineOK,
      false, TestOutcome::Anomaly, false,
      false, TestOutcome::Exception, false,
      true, TestOutcome::Success, true)
   {
      _protected_consoleMock->WriteColorMock.Expect();
      _protected_consoleMock->WriteMock.Expect();

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      string testResultThreeDecimalMillisecondsString;
      if (expectWriteLineOK)
      {
         _protected_consoleMock->WriteColorMock.Expect();
         _protected_consoleMock->WriteLineMock.Expect();
         testResultThreeDecimalMillisecondsString = testClassResultMock.
            MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();
      }
      TestMock testMock;

      TestResult testResult;
      testResult.testOutcome = newableDeletableTestOutcome;
      testResult.microseconds = ZenUnit::Random<unsigned>();
      const vector<TestResult> testResults{ testResult };
      testMock.RunTestMock.Return(testResults);
      //
      const bool testClassTypeIsNewableAndDeletable = _specificTestClassRunner->
         ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
      //
      if (expectWriteLineOK)
      {
         ZENMOCK(_protected_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "|", Color::Green },
            { "OK ", Color::Green }
         }));
         ZENMOCK(testClassResultMock.MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.
            CalledOnceWith(testResult.microseconds));
         ZENMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(testResultThreeDecimalMillisecondsString));
      }
      else
      {
         ZENMOCK(_protected_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      }
      ZENMOCK(_protected_consoleMock->WriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> "));
      ZENMOCK(testMock.RunTestMock.CalledOnce());
      ZENMOCK(testClassResultMock.AddTestResultsMock.CalledOnceWith(testResults));
      ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
   }

   TEST(RunTest_TestNameFiltersAreNonEmpty_NoneOfTheTestNameFiltersMatchTheTestName_DoesNotRunTest)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.testNameFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      GetZenUnitArgsMock.Return(zenUnitArgs);

      TestMock* const testMock = new TestMock;
      const string testName = Random<string>();
      testMock->NameMock.Return(testName.c_str());
      const unique_ptr<Test> test(testMock);

      _protected_twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);

      TestClassResultMock testClassResultMock;
      //
      _specificTestClassRunner->RunTest(test, &testClassResultMock);
      //
      ZENMOCK(GetZenUnitArgsMock.CalledOnce());
      ZENMOCK(testMock->NameMock.CalledOnce());
      ZENMOCK(_protected_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         zenUnitArgs.testNameFilters, _specificTestClassRunner.get(), &TestClassRunner::TestNameFilterMatchesTestName, testName.c_str()));
   }

   TEST2X2(RunTest_TestNameFiltersAreEmptyOrIfNotEmptyATestNameFilterMatchesTheTestName_RunsTest,
      size_t testNameFiltersSize, bool expectAnyerCall,
      0, false,
      1, true,
      2, true)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.testNameFilters.resize(testNameFiltersSize);
      GetZenUnitArgsMock.Return(zenUnitArgs);

      _protected_consoleMock->WriteColorMock.Expect();
      _protected_consoleMock->WriteMock.Expect();

      TestMock* const testMock = new TestMock;
      const string testName = Random<string>();
      testMock->NameMock.Return(testName.c_str());
      testMock->WritePostTestNameMessageMock.Expect();
      TestResult test0;
      test0.fullTestName = FullTestName("", "Test0", 0);
      const vector<TestResult> TestResults{ test0, TestResult() };
      testMock->RunTestMock.Return(TestResults);
      testMock->WritePostTestCompletionMessageMock.Expect();
      const unique_ptr<Test> test(testMock);
      if (expectAnyerCall)
      {
         _protected_twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
      }
      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      _specificTestClassRunner->RunTest(test, &testClassResultMock);
      //
      ZENMOCK(GetZenUnitArgsMock.CalledOnce());
      ZENMOCK(testMock->NameMock.CalledOnce());
      if (expectAnyerCall)
      {
         ZENMOCK(_protected_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
            zenUnitArgs.testNameFilters, _specificTestClassRunner.get(), &TestClassRunner::TestNameFilterMatchesTestName, testName.c_str()));
      }
      ZENMOCK(_protected_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      ZENMOCK(_protected_consoleMock->WriteMock.CalledOnceWith(testName));
      ZENMOCK(testMock->WritePostTestNameMessageMock.CalledOnceWith(_specificTestClassRunner->_protected_console.get()));
      ZENMOCK(testMock->RunTestMock.CalledOnce());
      ZENMOCK(testClassResultMock.AddTestResultsMock.CalledOnceWith(TestResults));
      ZENMOCK(testMock->WritePostTestCompletionMessageMock.CalledOnceWith(
         _specificTestClassRunner->_protected_console.get(), test0));
   }

   TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestClassResultLineMock.Expect();
      //
      _specificTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
      //
      ZENMOCK(testClassResultMock.PrintTestClassResultLineMock.CalledOnceWith(_protected_consoleMock));
   }

   RUN_TESTS(SpecificTestClassRunnerTests)
}
