#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestCasesAccumulatorMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestClassResultMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TwoArgAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TwoArgMemberForEacherMock.h"

namespace ZenUnit
{
   TESTS(SpecificTestClassRunnerTests)
   AFACT(OneArgConstructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
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

   // Base Class Function Callers
   using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
      std::vector<TestNameFilter>, TestClassRunner,
      bool(TestClassRunner::*)(const TestNameFilter&, const char*) const, const char*>;
   TwoArgMemberAnyerMockType* _protected_twoArgMemberAnyerMock = nullptr;

   // Base Class Constant Components
   ConsoleMock* _protected_consoleMock = nullptr;

   // Function Pointers
   METALMOCK_NONVOID1_FREE(string, _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString, unsigned)
   METALMOCK_NONVOID0_FREE(const ZenUnitArgs&, _call_ZenUnitTestRunner_GetZenUnitArgs)

   // Function Callers
   using _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMockType =
      NonVoidOneArgMemberFunctionCallerMock<TestResult, SpecificTestClassRunner<TestingTestClass>, Test*>;
   _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMockType* _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock = nullptr;

   using TwoArgTestAnyerMockType = TwoArgAnyerMock<
      const std::vector<std::unique_ptr<Test>>,
      bool(*)(const std::unique_ptr<Test>&, const TestNameFilter&),
      const TestNameFilter&>;
   TwoArgTestAnyerMockType* _twoArgTestAnyerMock = nullptr;

   using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
      unique_ptr<Test>, SpecificTestClassRunner<TestingTestClass>,
      void (SpecificTestClassRunner<TestingTestClass>::*)(
         const unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
   TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock = nullptr;

   VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>* _voidZeroArgMemberFunctionCallerMock = nullptr;
   VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>* _voidOneArgMemberFunctionCallerMock = nullptr;

   // Constant Components
   TestCasesAccumulatorMock* _testCasesAccumulatorMock = nullptr;

   const string _testClassName = ZenUnit::Random<string>();

   STARTUP
   {
      _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
      // Base Class Function Callers
      _specificTestClassRunner->_protected_twoArgMemberAnyer.reset(_protected_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
      // Base Class Constant Components
      _specificTestClassRunner->_protected_console.reset(_protected_consoleMock = new ConsoleMock);
      // Function Pointers
      _specificTestClassRunner->_call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString = BIND_1ARG_METALMOCK_OBJECT(_call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsStringMock);
      _specificTestClassRunner->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(_call_ZenUnitTestRunner_GetZenUnitArgsMock);
      // Function Callers
      _specificTestClassRunner->_caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests.reset(
         _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock = new _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMockType);
      _specificTestClassRunner->_twoArgTestAnyer.reset(_twoArgTestAnyerMock = new TwoArgTestAnyerMockType);
      _specificTestClassRunner->_twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      _specificTestClassRunner->_voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
      _specificTestClassRunner->_voidOneArgMemberFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock = new VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>);
      // Constant Components
      _specificTestClassRunner->_testCasesAccumulator.reset(_testCasesAccumulatorMock = new TestCasesAccumulatorMock);
   }

   TEST(OneArgConstructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   {
      SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(_testClassName.c_str());
      // Protected Function Callers
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._protected_twoArgMemberAnyer);
      // Protected Constant Components
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._protected_console);
      // Function Pointers
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, specificTestClassRunner._call_ZenUnitTestRunner_GetZenUnitArgs);
      // Function Callers
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString, specificTestClassRunner._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, specificTestClassRunner._call_ZenUnitTestRunner_GetZenUnitArgs);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgTestAnyer);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgMemberForEacher);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidZeroArgMemberFunctionCaller);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidOneArgMemberFunctionCaller);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._testCasesAccumulator);

      ARE_EQUAL(_testClassName.c_str(), specificTestClassRunner._testClassName);
      vector<unique_ptr<Test>> expectedTests;
      expectedTests.emplace_back(nullptr);
      VECTORS_ARE_EQUAL(expectedTests, specificTestClassRunner._tests);
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
      METALMOCK(_twoArgTestAnyerMock->TwoArgAnyMock.CalledOnceWith(
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
      METALMOCK(testMock->NameMock.CalledOnce());
      METALMOCK(testNameFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
      ARE_EQUAL(testNameFilterMatchesTestName, returnedTestNameFilterMatchesTestName);
   }

   TEST(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   {
      _specificTestClassRunner->_tests.resize(3);

      TestMock* const testMockA = new TestMock;
      testMockA->NumberOfTestCasesMock.Return(10ull);

      TestMock* const testMockB = new TestMock;
      testMockB->NumberOfTestCasesMock.Return(0ull);

      TestMock* const testMockC = new TestMock;
      testMockC->NumberOfTestCasesMock.Return(20ull);

      _specificTestClassRunner->_tests[0].reset(testMockA);
      _specificTestClassRunner->_tests[1].reset(testMockB);
      _specificTestClassRunner->_tests[2].reset(testMockC);
      //
      const size_t numberOfTestCases = _specificTestClassRunner->NumberOfTestCases();
      //
      METALMOCK(testMockA->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(testMockB->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(testMockC->NumberOfTestCasesMock.CalledOnce());
      ARE_EQUAL(30, numberOfTestCases);
   }

   TEST2X2(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ConfirmsTestClassNewableAndDeletable_RunsTests_PrintsAndReturnsTestClassResult,
      TestOutcome testOutcome, bool expectDoRunTestsCall,
      TestOutcome::Anomaly, false,
      TestOutcome::Exception, false,
      TestOutcome::Success, true)
   {
      _voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();

      TestResult testClassIsNewableAndDeletableTestResult;
      testClassIsNewableAndDeletableTestResult.testOutcome = testOutcome;
      _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock->CallConstMemberFunctionMock.Return(testClassIsNewableAndDeletableTestResult);

      const size_t numberOfTestResults = ZenUnit::RandomBetween<size_t>(1, 3);
      _testCasesAccumulatorMock->SumNumberOfTestCasesMock.Return(numberOfTestResults);

      if (expectDoRunTestsCall)
      {
         _voidZeroArgMemberFunctionCallerMock->CallNonConstMemberFunctionMock.Expect();
      }
      _voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();
      _protected_consoleMock->WriteNewLineMock.Expect();
      _specificTestClassRunner->_testClassResult = TestingNonDefaultTestClassResult();
      TestClassResult expectedResultingTestClassResult = _specificTestClassRunner->_testClassResult;
      expectedResultingTestClassResult.AddTestResult(testClassIsNewableAndDeletableTestResult);
      //
      const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
      //
      METALMOCK(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassNameAndNumberOfNamedTests));

      METALMOCK(_caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
         &_specificTestClassRunner->_newableDeletableTest));

      METALMOCK(_testCasesAccumulatorMock->SumNumberOfTestCasesMock.CalledOnceWith(&_specificTestClassRunner->_tests));

      constexpr size_t NewableAndDeletableTestResult = 1;
      ARE_EQUAL(NewableAndDeletableTestResult + numberOfTestResults, testClassResult._testResults.capacity());

      if (expectDoRunTestsCall)
      {
         METALMOCK(_voidZeroArgMemberFunctionCallerMock->CallNonConstMemberFunctionMock.CalledOnceWith(
            _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
      }
      METALMOCK(_voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassResultLine,
         &_specificTestClassRunner->_testClassResult));
      METALMOCK(_protected_consoleMock->WriteNewLineMock.CalledOnce());
      ARE_EQUAL(expectedResultingTestClassResult, testClassResult);
      IS_DEFAULT_VALUE(_specificTestClassRunner->_testClassResult); // Assertion that _testClassResult was std::moved from
   }

   TEST2X2(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests,
      bool randomTestOrdering, bool expectRandomForEach,
      false, false,
      true, true)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.randomTestOrdering = randomTestOrdering;
      _call_ZenUnitTestRunner_GetZenUnitArgsMock.Return(zenUnitArgs);
      if (expectRandomForEach)
      {
         _twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.Expect();
      }
      else
      {
         _twoArgMemberForEacherMock->TwoArgMemberForEachMock.Expect();
      }
      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      //
      _specificTestClassRunner->DoRunTests();
      //
      METALMOCK(_call_ZenUnitTestRunner_GetZenUnitArgsMock.CalledOnce());
      if (expectRandomForEach)
      {
         METALMOCK(_twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult,
            globalZenUnitModeRandomSeed));
      }
      else
      {
         METALMOCK(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult));
      }
   }

   TEST2X2(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests,
      size_t numberOfTests, bool expectTestsPlural,
      0ULL, true,
      1ULL, false,
      2ULL, true,
      3ULL, true)
   {
      _protected_consoleMock->WriteColorMock.Expect();
      _protected_consoleMock->WriteLineMock.Expect();
      _specificTestClassRunner->_testClassName = _testClassName.c_str();
      _specificTestClassRunner->_tests.resize(numberOfTests);
      //
      _specificTestClassRunner->PrintTestClassNameAndNumberOfNamedTests();
      //
      METALMOCK(_protected_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { "@", Color::Green },
         { _testClassName.c_str(), Color::Green }
      }));
      if (expectTestsPlural)
      {
         const string expectedRunningTestsMessage = String::ConcatValues(" | Running ", numberOfTests, " tests");
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningTestsMessage));
      }
      else
      {
         const string expectedRunningTestMessage = String::ConcatValues(" | Running ", numberOfTests, " test");
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningTestMessage));
      }
   }

   TEST2X2(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable,
      TestOutcome newableDeletableTestOutcome, bool expectWriteLineOK,
      TestOutcome::Anomaly, false,
      TestOutcome::Exception, false,
      TestOutcome::Success, true)
   {
      _protected_consoleMock->WriteColorMock.Expect();
      _protected_consoleMock->WriteMock.Expect();

      string testResultThreeDecimalMillisecondsString;
      if (expectWriteLineOK)
      {
         _protected_consoleMock->WriteColorMock.Expect();
         _protected_consoleMock->WriteLineMock.Expect();
         testResultThreeDecimalMillisecondsString = _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();
      }
      TestMock testMock;

      TestResult newableAndDeletableTestResult;
      newableAndDeletableTestResult.testOutcome = newableDeletableTestOutcome;
      newableAndDeletableTestResult.elapsedMicroseconds = ZenUnit::Random<unsigned>();
      const vector<TestResult> newableAndDeletableTestResults{ newableAndDeletableTestResult };
      testMock.RunTestMock.Return(newableAndDeletableTestResults);
      //
      const TestResult returnedNewableAndDeletableTestResult = _specificTestClassRunner->ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock);
      //
      if (expectWriteLineOK)
      {
         METALMOCK(_protected_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "|", Color::Green },
            { "OK ", Color::Green }
         }));
         METALMOCK(_call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.CalledOnceWith(newableAndDeletableTestResult.elapsedMicroseconds));
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(testResultThreeDecimalMillisecondsString));
      }
      else
      {
         METALMOCK(_protected_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      }
      METALMOCK(_protected_consoleMock->WriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> "));
      METALMOCK(testMock.RunTestMock.CalledOnce());
      ARE_EQUAL(newableAndDeletableTestResult, returnedNewableAndDeletableTestResult);
   }

   TEST(RunTest_TestNameFiltersAreNonEmpty_NoneOfTheTestNameFiltersMatchTheTestName_DoesNotRunTest)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.testNameFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      _call_ZenUnitTestRunner_GetZenUnitArgsMock.Return(zenUnitArgs);

      TestMock* const testMock = new TestMock;
      const string testName = Random<string>();
      testMock->NameMock.Return(testName.c_str());
      const unique_ptr<Test> test(testMock);

      _protected_twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);

      TestClassResultMock testClassResultMock;
      //
      _specificTestClassRunner->RunTest(test, &testClassResultMock);
      //
      METALMOCK(_call_ZenUnitTestRunner_GetZenUnitArgsMock.CalledOnce());
      METALMOCK(testMock->NameMock.CalledOnce());
      METALMOCK(_protected_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         zenUnitArgs.testNameFilters, _specificTestClassRunner.get(), &TestClassRunner::TestNameFilterMatchesTestName, testName.c_str()));
   }

   TEST2X2(RunTest_TestNameFiltersAreEmptyOrIfNotEmptyATestNameFilterMatchesTheTestName_RunsTest,
      size_t testNameFiltersSize, bool expectAnyerCall,
      0ULL, false,
      1ULL, true,
      2ULL, true)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.testNameFilters.resize(testNameFiltersSize);
      _call_ZenUnitTestRunner_GetZenUnitArgsMock.Return(zenUnitArgs);

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
      METALMOCK(_call_ZenUnitTestRunner_GetZenUnitArgsMock.CalledOnce());
      METALMOCK(testMock->NameMock.CalledOnce());
      if (expectAnyerCall)
      {
         METALMOCK(_protected_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
            zenUnitArgs.testNameFilters, _specificTestClassRunner.get(), &TestClassRunner::TestNameFilterMatchesTestName, testName.c_str()));
      }
      METALMOCK(_protected_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      METALMOCK(_protected_consoleMock->WriteMock.CalledOnceWith(testName));
      METALMOCK(testMock->WritePostTestNameMessageMock.CalledOnceWith(_specificTestClassRunner->_protected_console.get()));
      METALMOCK(testMock->RunTestMock.CalledOnce());
      METALMOCK(testClassResultMock.AddTestResultsMock.CalledOnceWith(TestResults));
      METALMOCK(testMock->WritePostTestCompletionMessageMock.CalledOnceWith(
         _specificTestClassRunner->_protected_console.get(), test0));
   }

   TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestClassResultLineMock.Expect();
      //
      _specificTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
      //
      METALMOCK(testClassResultMock.PrintTestClassResultLineMock.CalledOnceWith(_protected_consoleMock));
   }

   RUN_TESTS(SpecificTestClassRunnerTests)
}
