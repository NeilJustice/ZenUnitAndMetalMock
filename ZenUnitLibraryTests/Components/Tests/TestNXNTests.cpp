#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/ITestCaseNumberGeneratorMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/ThreeArgAnyerMock.h"

namespace ZenUnit
{
   static const size_t N = 1;

   TESTS(TestNXNTests)
   AFACT(Constructor_NewsComponents_SetsFields_MakesGettersReturnExpected)
   AFACT(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   AFACT(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   AFACT(RunTest_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   AFACT(RunTestCaseIfNotFilteredOut_ShouldNotRunTestCase_DoesNotCallRunTestCase)
   AFACT(RunTestCaseIfNotFilteredOut_ShouldRunTestCase_CallsRunTestCase)
   AFACT(RunTestCase_1X1_DoesSo)
   AFACT(RunTestCase_2X2_DoesSo)
   AFACT(Exit1IfInvalidTestCaseNumberSpecified_NonEmptyTestResults_DoesNotThrowException)
   AFACT(Exit1IfInvalidTestCaseNumberSpecified_EmptyTestResults_WritesErrorMessage_Exits1)
   AFACT(ShouldRunTestCase_TestNameFiltersAreEmpty_ReturnsTrue)
   FACTS(ShouldRunTestCase_TestNameFiltersAreNonEmpty_ReturnsTrueIfAnyTestNameFilterMatchesTestClassNameTestNameTestCaseNumber)
   AFACT(TestNameFilterMatchesTestCase_ReturnsTrueIfTestNameFilterMatchesTestCaseNumberAndTestClassNameAndTestName)
   AFACT(NewTestClass_NewsTestClass)
   AFACT(Startup_CallsTestClassStartup)
   AFACT(TestBody_CallsRunNXNTestCase)
   AFACT(RunNXNTestCase_DoesNotThrowException)
   AFACT(Cleanup_CallsCleanup)
   AFACT(DeleteTestClass_DeletesTestClass)
   FACTS(PrintTestCaseNumberThenArgsThenArrow_WritesTestCaseNumberArrow)
   AFACT(WriteLineOKIfSuccessOrSuccessButPastDeadline_CallsTestResultWriteLineOKIfSuccessOrSuccessButPastDeadline)
   EVIDENCE

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   // Function Pointers
   METALMOCK_VOID1_FREE(_call_quick_exit, int)
   METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, _call_GetZenUnitArgs)
   using CallerOfTestNameFilterMatchesTestCaseMockType = ThreeArgAnyerMock<
      std::vector<TestNameFilter>, bool(*)(const TestNameFilter&, const FullTestName&, size_t), const FullTestName&, size_t>;
   // Function Callers
   CallerOfTestNameFilterMatchesTestCaseMockType* _callerOfTestNameFilterMatchesTestCaseMock = nullptr;
   // Constant Components
   ConsoleMock* _consoleMock = nullptr;

   const string _testClassName = Random<string>();
   const string _testName = Random<string>();
   const string _testCaseArgsText = Random<string>();

   STARTUP
   {
      _testNXN = make_unique<TestNXN<TestingTestClass, N, int>>("", "", "", 0);
      // Function Pointers
      _testNXN->_call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
      _testNXN->_call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(_call_GetZenUnitArgsMock);
      // Function Callers
      _testNXN->_callerOfTestNameFilterMatchesTestCase.reset(_callerOfTestNameFilterMatchesTestCaseMock = new CallerOfTestNameFilterMatchesTestCaseMockType);
      // Constant Components
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(Constructor_NewsComponents_SetsFields_MakesGettersReturnExpected)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> test2X2(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0, 0, 0);

      // Function Pointers
      STD_FUNCTION_TARGETS(::quick_exit, test2X2._call_quick_exit);
      STD_FUNCTION_TARGETS(ITestCaseNumberGenerator::FactoryNew, test2X2._call_ITestCaseNumberGeneratorFactoryNew);
      STD_FUNCTION_TARGETS(String::SplitOnNonQuotedCommas, test2X2._call_String_SplitOnNonQuotedCommas);
      STD_FUNCTION_TARGETS(ZenUnitTestRunner::GetZenUnitArgs, test2X2._call_ZenUnitTestRunner_GetZenUnitArgs);
      // Function Callers
      DELETE_TO_ASSERT_NEWED(test2X2._callerOfTestNameFilterMatchesTestCase);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(test2X2._console);
      // Mutable Fields
      ARE_EQUAL(_testCaseArgsText, test2X2._testCaseArgsText);
      IS_NULLPTR(test2X2._testClass);
      ARE_EQUAL(1, test2X2._currentTestCaseNumber);
      IS_EMPTY(test2X2._testResults);
      const size_t expectedNumberOfTestCases = 2;
      ARE_EQUAL(expectedNumberOfTestCases, test2X2._testResults.capacity());

      // Getters
      ARE_EQUAL(_testName, test2X2.Name());
      const string expectedFullName = String::ConcatStrings("TESTS(", _testClassName, ")\nTEST2X2(", _testName, ")");
      ARE_EQUAL(expectedFullName, test2X2.FullName());
      ARE_EQUAL("(0)", test2X2.FilePathLineNumberString());
   }

   TEST(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN_1X1_1Arg(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0);
      ARE_EQUAL(tuple<int>(0), testNXN_1X1_1Arg._protected_testCaseArgs);

      const TestNXN<TestingTestClass, 1, int, int> testNXN_1X1_2Args(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0);
      const tuple<int, int> expectedTestCaseArgs1(0, 0);
      ARE_EQUAL(expectedTestCaseArgs1, testNXN_1X1_2Args._protected_testCaseArgs);

      const TestNXN<TestingTestClass, 2, const string&, volatile int> testNXN_2X2_4Args(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), string(), 100);
      const tuple<string, int> expectedTestCaseArgs2(string(), 100);
      ARE_EQUAL(expectedTestCaseArgs2, testNXN_2X2_4Args._protected_testCaseArgs);
   }

   TEST(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   {
      const TestNXN<TestingTestClass, 1, int>
         test1X1(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0);
      ARE_EQUAL(1, test1X1.NumberOfTestCases());

      const TestNXN<TestingTestClass, 1, int, int>
         test1X1_2Args(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(2, test1X1_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int>
         test2X2_2Args(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(1, test2X2_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int, int, int>
         test2X2_4Args(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0, 0, 0);
      ARE_EQUAL(2, test2X2_4Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 3, int, int, int, int, int, int, int, int, int>
         test3X3_9Args(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0, 0, 0, 0, 0, 0, 0, 0);
      ARE_EQUAL(3, test3X3_9Args.NumberOfTestCases());
   }

   TEST(RunTest_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   {
      class Test1X1SelfMocked : public Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
      public:
         METALMOCK_VOID3(RunTestCaseIfNotFilteredOut, size_t, const ZenUnitArgs&, const std::vector<std::string>&)
         METALMOCK_VOID0_CONST(Exit1IfInvalidTestCaseNumberSpecified)
         METALMOCK_NONVOID1_STATIC(std::shared_ptr<ITestCaseNumberGenerator>, ITestCaseNumberGenerator, FactoryNew, bool)

         Test1X1SelfMocked() noexcept
            : Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>(
               "", // testClassName
               "", // testName
               "", // testCaseArgsText
               0, // test case arg 0
               0 // test case arg 1
               )
            {
               _call_ITestCaseNumberGeneratorFactoryNew = BIND_1ARG_METALMOCK_OBJECT(FactoryNewMock);
            }
      } test1X1SelfMocked;

      METALMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::ZenUnitTestRunner, GetArgs)

      const ZenUnitArgs args = GetArgsMock.ReturnRandom();
      test1X1SelfMocked._call_ZenUnitTestRunner_GetZenUnitArgs = BIND_0ARG_METALMOCK_OBJECT(GetArgsMock);

      shared_ptr<ITestCaseNumberGeneratorMock> testCaseNumberGeneratorMock = make_shared<ITestCaseNumberGeneratorMock>();
      testCaseNumberGeneratorMock->InitializeMock.Expect();
      testCaseNumberGeneratorMock->NextTestCaseNumberMock.ReturnValues(1ULL, 2ULL, std::numeric_limits<size_t>::max());
      test1X1SelfMocked.FactoryNewMock.Return(testCaseNumberGeneratorMock);

      METALMOCK_NONVOID0_STATIC(vector<string>, ZenUnit::String, SplitOnNonQuotedCommas)
      const vector<string> splitTestCaseArgs =
      {
         ZenUnit::Random<string>(),
         ZenUnit::Random<string>(),
         ZenUnit::Random<string>()
      };
      SplitOnNonQuotedCommasMock.Return(splitTestCaseArgs);
      test1X1SelfMocked._call_String_SplitOnNonQuotedCommas = BIND_0ARG_METALMOCK_OBJECT(SplitOnNonQuotedCommasMock);

      test1X1SelfMocked.Exit1IfInvalidTestCaseNumberSpecifiedMock.Expect();

      TestResult firstTestResult;
      const string firstTestName = ZenUnit::Random<string>();
      firstTestResult.fullTestName.testName = firstTestName.c_str();

      TestResult secondTestResult;
      const string secondTestName = ZenUnit::Random<string>();
      secondTestResult.fullTestName.testName = secondTestName.c_str();

      test1X1SelfMocked.RunTestCaseIfNotFilteredOutMock.Expect();
      //
      const vector<TestResult> testResults = test1X1SelfMocked.RunTest();
      //
      METALMOCK(GetArgsMock.CalledOnce());
      METALMOCK(test1X1SelfMocked.FactoryNewMock.CalledOnceWith(args.randomTestOrdering));
      METALMOCK(testCaseNumberGeneratorMock->InitializeMock.CalledOnceWith(2, N));
      METALMOCK(SplitOnNonQuotedCommasMock.CalledOnce());
      METALMOCK(testCaseNumberGeneratorMock->NextTestCaseNumberMock.CalledNTimes(3));
      METALMOCK(test1X1SelfMocked.RunTestCaseIfNotFilteredOutMock.CalledAsFollows(
      {
         { 1, args, splitTestCaseArgs },
         { 2, args, splitTestCaseArgs }
      }));
      METALMOCK(test1X1SelfMocked.Exit1IfInvalidTestCaseNumberSpecifiedMock.CalledOnce());
      ARE_EQUAL(1, test1X1SelfMocked._currentTestCaseNumber);
      IS_EMPTY(testResults);
   }

   class Test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests : public Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>
   {
   public:
      METALMOCK_NONVOID3_CONST(bool, ShouldRunTestCase, const ZenUnitArgs&, const FullTestName&, size_t)
      METALMOCK_VOID2(RunTestCase, size_t, const std::vector<std::string>&)

      Test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests() noexcept
         : Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>(
            "", // testClassName
            "", // testName
            "", // testCaseArgsText
            0, // test case arg 0
            0 // test case arg 1
         )
      {
         _protected_fullTestName.testClassName = nonDefaultTestClassName.c_str();
      }
   private:
      const string nonDefaultTestClassName = ZenUnit::Random<string>();
   } test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests;

   TEST(RunTestCaseIfNotFilteredOut_ShouldNotRunTestCase_DoesNotCallRunTestCase)
   {
      test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.Return(false);
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.
         RunTestCaseIfNotFilteredOut(testCaseNumber, args, splitTestCaseArgs);
      //
      METALMOCK(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.CalledOnceWith(
         args, test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests._protected_fullTestName, testCaseNumber));
   }

   TEST(RunTestCaseIfNotFilteredOut_ShouldRunTestCase_CallsRunTestCase)
   {
      test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.Return(true);
      test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.RunTestCaseMock.Expect();
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.
         RunTestCaseIfNotFilteredOut(testCaseNumber, args, splitTestCaseArgs);
      //
      METALMOCK(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.CalledOnceWith(
         args, test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests._protected_fullTestName, testCaseNumber));
      METALMOCK(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.RunTestCaseMock.
         CalledOnceWith(testCaseNumber, splitTestCaseArgs));
   }

   TEST(RunTestCase_1X1_DoesSo)
   {
      class Test1X1SelfMocked : public Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
      public:
         METALMOCK_VOID2_CONST(PrintTestCaseNumberThenArgsThenArrow, size_t, const vector<string>&)
         METALMOCK_NONVOID0(TestResult, MockableCallBaseRunTest)
         METALMOCK_VOID1_CONST(WriteLineOKIfSuccessOrSuccessButPastDeadline, const TestResult&)
         Test1X1SelfMocked() noexcept
            : Metal::Mock<TestNXN<TestingTestClass, 1, int, int>>(
               "", // testClassName
               "", // testName
               "", // testCaseArgsText
               0, // test case arg 0
               0 // test case arg 1
               )
            {
            }
      } test1X1SelfMocked;

      test1X1SelfMocked.PrintTestCaseNumberThenArgsThenArrowMock.Expect();

      TestResult testResult;
      const string testName = ZenUnit::Random<string>();
      testResult.fullTestName.testName = testName.c_str();
      test1X1SelfMocked.MockableCallBaseRunTestMock.Return(testResult);

      test1X1SelfMocked.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.Expect();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test1X1SelfMocked.RunTestCase(testCaseNumber, splitTestCaseArgs);
      //
      METALMOCK(test1X1SelfMocked.PrintTestCaseNumberThenArgsThenArrowMock.CalledOnceWith(testCaseNumber, splitTestCaseArgs));
      METALMOCK(test1X1SelfMocked.MockableCallBaseRunTestMock.CalledOnce());
      TestResult expectedTestResult;
      expectedTestResult.testCaseNumber = testCaseNumber;
      expectedTestResult.totalTestCases = 2;
      expectedTestResult.fullTestName.testName = testName.c_str();
      METALMOCK(test1X1SelfMocked.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.CalledOnceWith(expectedTestResult));
      vector<TestResult> expectedResulingTestResults = { expectedTestResult };
      VECTORS_ARE_EQUAL(expectedResulingTestResults, test1X1SelfMocked._testResults);
   }

   TEST(RunTestCase_2X2_DoesSo)
   {
      class Test2X2SelfMocked : public Metal::Mock<TestNXN<TestingTestClass, 2, int, int, int, int, int, int>>
      {
      public:
         METALMOCK_VOID2_CONST(PrintTestCaseNumberThenArgsThenArrow, size_t, const vector<string>&)
         METALMOCK_NONVOID0(TestResult, MockableCallBaseRunTest)
         METALMOCK_VOID1_CONST(WriteLineOKIfSuccessOrSuccessButPastDeadline, const TestResult&)
         Test2X2SelfMocked() noexcept
            : Metal::Mock<TestNXN<TestingTestClass, 2, int, int, int, int, int, int>>(
               "", // testClassName
               "", // testName
               "", // testCaseArgsText
               0, 0,
               0, 0,
               0, 0)
            {
            }
      } test2X2SelfMocked;

      test2X2SelfMocked.PrintTestCaseNumberThenArgsThenArrowMock.Expect();

      TestResult testResult;
      const string testName = ZenUnit::Random<string>();
      testResult.fullTestName.testName = testName.c_str();
      test2X2SelfMocked.MockableCallBaseRunTestMock.Return(testResult);

      test2X2SelfMocked.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.Expect();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test2X2SelfMocked.RunTestCase(testCaseNumber, splitTestCaseArgs);
      //
      METALMOCK(test2X2SelfMocked.PrintTestCaseNumberThenArgsThenArrowMock.CalledOnceWith(testCaseNumber, splitTestCaseArgs));
      METALMOCK(test2X2SelfMocked.MockableCallBaseRunTestMock.CalledOnce());
      TestResult expectedTestResult;
      expectedTestResult.testCaseNumber = testCaseNumber;
      expectedTestResult.totalTestCases = 3;
      expectedTestResult.fullTestName.testName = testName.c_str();
      METALMOCK(test2X2SelfMocked.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.CalledOnceWith(expectedTestResult));
      vector<TestResult> expectedResulingTestResults = { expectedTestResult };
      VECTORS_ARE_EQUAL(expectedResulingTestResults, test2X2SelfMocked._testResults);
   }

   TEST(Exit1IfInvalidTestCaseNumberSpecified_NonEmptyTestResults_DoesNotThrowException)
   {
      _testNXN->_testResults.resize(1);
      _testNXN->Exit1IfInvalidTestCaseNumberSpecified();
   }

   TEST(Exit1IfInvalidTestCaseNumberSpecified_EmptyTestResults_WritesErrorMessage_Exits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _call_quick_exitMock.Expect();
      IS_EMPTY(_testNXN->_testResults);
      //
      _testNXN->Exit1IfInvalidTestCaseNumberSpecified();
      //
      const std::string expectedErrorMessage = "\nError: Invalid test case number specified in --run filter. Exiting with code 1.";
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      METALMOCK(_call_quick_exitMock.CalledOnceWith(1));
   }

   TEST(ShouldRunTestCase_TestNameFiltersAreEmpty_ReturnsTrue)
   {
      const ZenUnitArgs zenUnitArgs;
      IS_EMPTY(zenUnitArgs.testNameFilters);
      const FullTestName fullTestName;
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool shouldRunTestCase = _testNXN->ShouldRunTestCase(zenUnitArgs, fullTestName, testCaseNumber);
      //
      IS_TRUE(shouldRunTestCase);
   }

   TEST2X2(ShouldRunTestCase_TestNameFiltersAreNonEmpty_ReturnsTrueIfAnyTestNameFilterMatchesTestClassNameTestNameTestCaseNumber,
      bool anyTestNameFilterMatchesThisTest, bool expectedReturnValue,
      false, false,
      true, true)
   {
      _callerOfTestNameFilterMatchesTestCaseMock->ThreeArgAnyMock.Return(anyTestNameFilterMatchesThisTest);
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.testNameFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      FullTestName fullTestName;
      const string nonDefaultTestClassName = ZenUnit::Random<string>();
      fullTestName.testClassName = nonDefaultTestClassName.c_str();
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool shouldRunTestCase = _testNXN->ShouldRunTestCase(zenUnitArgs, fullTestName, testCaseNumber);
      //
      METALMOCK(_callerOfTestNameFilterMatchesTestCaseMock->ThreeArgAnyMock.CalledOnceWith(
         zenUnitArgs.testNameFilters, TestNXN<TestingTestClass, N, int>::TestNameFilterMatchesTestCase, fullTestName, testCaseNumber));
      ARE_EQUAL(expectedReturnValue, shouldRunTestCase);
   }

   TEST(TestNameFilterMatchesTestCase_ReturnsTrueIfTestNameFilterMatchesTestCaseNumberAndTestClassNameAndTestName)
   {
      TestNameFilterMock testNameFilterMock;
      const bool testNameMatchesTestCase = testNameFilterMock.MatchesTestCaseMock.ReturnRandom();

      FullTestName fullTestName;
      const string testClassName = ZenUnit::Random<string>();
      const string testName = ZenUnit::Random<string>();
      fullTestName.testClassName = testClassName.c_str();
      fullTestName.testName = testName.c_str();
      fullTestName.arity = ZenUnit::Random<unsigned char>();
      const size_t testCaseNumber = ZenUnit::RandomNon0<size_t>();
      //
      const bool returnedTestNameMatchesTestCase =
         TestNXN<TestingTestClass, 1, int>::TestNameFilterMatchesTestCase(testNameFilterMock, fullTestName, testCaseNumber);
      //
      METALMOCK(testNameFilterMock.MatchesTestCaseMock.CalledOnceWith(
         fullTestName.testClassName, fullTestName.testName, testCaseNumber));
      ARE_EQUAL(testNameMatchesTestCase, returnedTestNameMatchesTestCase);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULLPTR(_testNXN->_testClass);
      //
      _testNXN->NewTestClass();
      //
      DELETE_TO_ASSERT_NEWED(_testNXN->_testClass);
      _testNXN->_testClass.reset();
   }

   TEST(Startup_CallsTestClassStartup)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->StartupMock.Expect();
      //
      _testNXN->Startup();
      //
      METALMOCK(_testNXN->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsRunNXNTestCase)
   {
      class TestNXN_RunNXNTestCaseMocked : public Metal::Mock<TestNXN<TestingTestClass, 1, int>>
      {
      public:
         METALMOCK_VOID2(RunNXNTestCase, TestingTestClass*, size_t)
            TestNXN_RunNXNTestCaseMocked() noexcept
            : Metal::Mock<TestNXN<TestingTestClass, 1, int>>("", "", "", 0)
         {
         }
      } testNXN_RunNXNTestCaseMocked;

      testNXN_RunNXNTestCaseMocked._testClass = make_unique<TestingTestClass>();
      const size_t currentTestCaseNumber = ZenUnit::Random<size_t>();
      testNXN_RunNXNTestCaseMocked._currentTestCaseNumber = currentTestCaseNumber;
      testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.Expect();
      //
      testNXN_RunNXNTestCaseMocked.TestBody();
      //
      const size_t expectedTestCaseArgsIndex = (currentTestCaseNumber - 1) * N;
      METALMOCK(testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.CalledOnceWith(
         testNXN_RunNXNTestCaseMocked._testClass.get(), expectedTestCaseArgsIndex));
   }

   TEST(RunNXNTestCase_DoesNotThrowException)
   {
      _testNXN->RunNXNTestCase(nullptr, 0);
   }

   TEST(Cleanup_CallsCleanup)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->CleanupMock.Expect();
      //
      _testNXN->Cleanup();
      //
      METALMOCK(_testNXN->_testClass->CleanupMock.CalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorHasBeenCalled);
      //
      _testNXN->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorHasBeenCalled);
   }

   TEST3X3(PrintTestCaseNumberThenArgsThenArrow_WritesTestCaseNumberArrow,
      size_t testCaseNumber, size_t expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      1ULL, 1ULL, 0ULL,
      2ULL, 2ULL, 1ULL,
      3ULL, 3ULL, 2ULL)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteSizeTMock.Expect();
      _consoleMock->WriteStringsCommaSeparatedMock.Expect();
      const vector<string> splitTestCaseArgs = { "Arg0", "Argument1" };
      //
      _testNXN->PrintTestCaseNumberThenArgsThenArrow(testCaseNumber, splitTestCaseArgs);
      //
      METALMOCK(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { " [", Color::Green },
         { "]", Color::Green }
      }));
      METALMOCK(_consoleMock->WriteStringsCommaSeparatedMock.CalledOnceWith(splitTestCaseArgs, expectedTestCaseArgsPrintingStartIndex, N));
      METALMOCK(_consoleMock->WriteMock.CalledAsFollows(
      {
         { " ("s },
         { ") -> "s }
      }));
      METALMOCK(_consoleMock->WriteSizeTMock.CalledOnceWith(expectedTestCaseNumber));
   }

   TEST(WriteLineOKIfSuccessOrSuccessButPastDeadline_CallsTestResultWriteLineOKIfSuccessOrSuccessButPastDeadline)
   {
      TestResultMock testResultMock;
      testResultMock.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.Expect();
      //
      _testNXN->WriteLineOKIfSuccessOrSuccessButPastDeadline(testResultMock);
      //
      METALMOCK(testResultMock.WriteLineOKIfSuccessOrSuccessButPastDeadlineMock.CalledOnceWith(_testNXN->_console.get()));
   }

   RUN_TESTS(TestNXNTests)


   template<typename T>
   TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, T)
   AFACT(NonParameterizedTest)
   FACTS(Test1X1Test)
   FACTS(Test2X2Test)
   FACTS(Test3X3Test)
   FACTS(Test4X4Test)
   FACTS(Test5X5Test)
   FACTS(Test6X6Test)
   FACTS(Test7X7Test)
   FACTS(Test8X8Test)
   FACTS(Test9X9Test)
   FACTS(Test10X10Test)
   EVIDENCE

   TEST(NonParameterizedTest) {}
   TEST1X1(Test1X1Test, int, 0) {}
   TEST2X2(Test2X2Test, int, int, 0, 0) {}
   TEST3X3(Test3X3Test, int, int, int, 0, 0, 0) {}
   TEST4X4(Test4X4Test, int, int, int, int, 0, 0, 0, 0) {}
   TEST5X5(Test5X5Test, int, int, int, int, int, 0, 0, 0, 0, 0) {}
   TEST6X6(Test6X6Test, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0) {}
   TEST7X7(Test7X7Test, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0) {}
   TEST8X8(Test8X8Test, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0) {}
   TEST9X9(Test9X9Test, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
   TEST10X10(Test10X10Test, int, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}

   RUN_TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, int)
}
