#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
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

   // Function Pointers
   METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetZenUnitArgs)

   // Function Callers
   using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
      std::vector<TestNameFilter>, TestClassRunner,
      bool(TestClassRunner::*)(const TestNameFilter&, const char*) const, const char*>;
   TwoArgMemberAnyerMockType* _protected_twoArgMemberAnyerMock = nullptr;

   ConsoleMock* _protected_consoleMock = nullptr;

   NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<
      TestingTestClass>, Test*, TestClassResult*>* _nonVoidTwoArgFunctionCallerMock = nullptr;

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

   const string _testClassName = ZenUnit::Random<string>();

   STARTUP
   {
      _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
      // Protected Function Callers
      _specificTestClassRunner->_protected_twoArgMemberAnyer.reset(_protected_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
      // Protected Constant Components
      _specificTestClassRunner->_protected_console.reset(_protected_consoleMock = new ConsoleMock);
      // Function Pointers
      _specificTestClassRunner->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(GetZenUnitArgsMock);
      // Function Callers
      _specificTestClassRunner->_nonVoidTwoArgFunctionCaller.reset(_nonVoidTwoArgFunctionCallerMock = new NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>);
      _specificTestClassRunner->_twoArgTestAnyer.reset(_twoArgTestAnyerMock = new TwoArgTestAnyerMockType);
      _specificTestClassRunner->_twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      _specificTestClassRunner->_voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
      _specificTestClassRunner->_voidOneArgMemberFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock = new VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>);
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
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._nonVoidTwoArgFunctionCaller);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgTestAnyer);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._twoArgMemberForEacher);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidZeroArgMemberFunctionCaller);
      DELETE_TO_ASSERT_NEWED(specificTestClassRunner._voidOneArgMemberFunctionCaller);

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
      bool testClassTypeNewableAndDeletable, bool expectDoRunTestsCall,
      false, false,
      true, true)
   {
      _voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();
      _nonVoidTwoArgFunctionCallerMock->CallConstMemberFunctionMock.Return(testClassTypeNewableAndDeletable);
      if (expectDoRunTestsCall)
      {
         _voidZeroArgMemberFunctionCallerMock->CallNonConstMemberFunctionMock.Expect();
      }
      _voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();
      _protected_consoleMock->WriteNewLineMock.Expect();
      _specificTestClassRunner->_testClassResult = TestClassResult::TestingNonDefault();
      //
      const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
      //
      METALMOCK(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassNameAndNumberOfNamedTests));
      METALMOCK(_nonVoidTwoArgFunctionCallerMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
         &_specificTestClassRunner->_newableDeletableTest, &_specificTestClassRunner->_testClassResult));
      if (expectDoRunTestsCall)
      {
         METALMOCK(_voidZeroArgMemberFunctionCallerMock->CallNonConstMemberFunctionMock.CalledOnceWith(
            _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
      }
      METALMOCK(_voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassResultLine,
         &_specificTestClassRunner->_testClassResult));
      METALMOCK(_protected_consoleMock->WriteNewLineMock.CalledOnce());
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
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      if (expectRandomForEach)
      {
         METALMOCK(_twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult,
            zenUnitArgs.randomSeed));
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
      0ull, true,
      1ull, false,
      2ull, true,
      3ull, true)
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
         const string expectedRunningTestsMessage = String::Concat(" | Running ", numberOfTests, " tests");
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningTestsMessage));
      }
      else
      {
         const string expectedRunningTestMessage = String::Concat(" | Running ", numberOfTests, " test");
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningTestMessage));
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
         METALMOCK(_protected_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "|", Color::Green },
            { "OK ", Color::Green }
         }));
         METALMOCK(testClassResultMock.MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.
            CalledOnceWith(testResult.microseconds));
         METALMOCK(_protected_consoleMock->WriteLineMock.CalledOnceWith(testResultThreeDecimalMillisecondsString));
      }
      else
      {
         METALMOCK(_protected_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      }
      METALMOCK(_protected_consoleMock->WriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> "));
      METALMOCK(testMock.RunTestMock.CalledOnce());
      METALMOCK(testClassResultMock.AddTestResultsMock.CalledOnceWith(testResults));
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
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
      METALMOCK(testMock->NameMock.CalledOnce());
      METALMOCK(_protected_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         zenUnitArgs.testNameFilters, _specificTestClassRunner.get(), &TestClassRunner::TestNameFilterMatchesTestName, testName.c_str()));
   }

   TEST2X2(RunTest_TestNameFiltersAreEmptyOrIfNotEmptyATestNameFilterMatchesTheTestName_RunsTest,
      size_t testNameFiltersSize, bool expectAnyerCall,
      0ull, false,
      1ull, true,
      2ull, true)
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
      METALMOCK(GetZenUnitArgsMock.CalledOnce());
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
