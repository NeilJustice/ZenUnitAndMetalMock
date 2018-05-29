#include "pch.h"
#include "ZenUnitTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Tests/Mock/ITestCaseNumberGeneratorMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ThreeArgAnyerMock.h"

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
   AFACT(RunTestCase_DoesSo)
   AFACT(Exit1IfNonExistentTestCaseNumberSpecified_NonEmptyTestResults_DoesNothing)
   AFACT(Exit1IfNonExistentTestCaseNumberSpecified_EmptyTestResults_WritesErrorMessage_Exits1)
   AFACT(ShouldRunTestCase_EmptyRunFilters_ReturnsTrue)
   FACTS(ShouldRunTestCase_NonEmptyRunFilters_ReturnsTrueIfAnyRunFilterMatchesTestClassNameTestNameTestCaseNumber)
   AFACT(RunFilterMatchesTestCase_ReturnsTrueIfRunFilterMatchesTestCaseNumberAndTestClassNameAndTestName)
   AFACT(NewTestClass_NewsTestClass)
   AFACT(Startup_CallsTestClassStartup)
   AFACT(TestBody_CallsRunNXNTestCase)
   AFACT(RunNXNTestCase_DoesNothing)
   AFACT(Cleanup_CallsCleanup)
   AFACT(DeleteTestClass_DeletesTestClass)
   FACTS(PrintTestCaseNumberThenArgsThenArrow_WritesTestCaseNumberArrow)
   AFACT(WriteLineOKIfSuccess_CallsTestResultWriteLineOKIfSuccess)
   EVIDENCE

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   ConsoleMock* _consoleMock = nullptr;
   using CallerOfRunFilterMatchesTestCaseMockType = ThreeArgAnyerMock<
      std::vector<RunFilter>, bool(*)(const RunFilter&, const FullTestName&, size_t), const FullTestName&, size_t>;
   CallerOfRunFilterMatchesTestCaseMockType* _callerOfRunFilterMatchesTestCaseMock = nullptr;
   const string _testClassName = Random<string>();
   const string _testName = Random<string>();
   const string _testCaseArgsText = Random<string>();
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)
   ZENMOCK_VOID1_GLOBAL(exit, int)

   STARTUP
   {
      _testNXN = make_unique<TestNXN<TestingTestClass, N, int>>("", "", "", 0);
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
      _testNXN->_callerOfRunFilterMatchesTestCase.reset(_callerOfRunFilterMatchesTestCaseMock = new CallerOfRunFilterMatchesTestCaseMockType);
      _testNXN->call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
      _testNXN->call_exit = BIND_1ARG_ZENMOCK_OBJECT(exit_ZenMockObject);
   }

   TEST(Constructor_NewsComponents_SetsFields_MakesGettersReturnExpected)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> test2X2(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0, 0, 0);

      // Fields
      POINTER_WAS_NEWED(test2X2._console);
      POINTER_WAS_NEWED(test2X2._callerOfRunFilterMatchesTestCase);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, test2X2.call_TestRunner_GetArgs);
      STD_FUNCTION_TARGETS(::exit, test2X2.call_exit);
      STD_FUNCTION_TARGETS(ITestCaseNumberGenerator::FactoryNew, test2X2.call_ITestCaseNumberGeneratorFactoryNew);
      STD_FUNCTION_TARGETS(String::CommaSplitExceptQuotedCommas, test2X2.call_String_CommaSplitExceptQuotedCommas);
      IS_NULL(test2X2._testClass);
      ARE_EQUAL(1, test2X2._currentTestCaseNumber);
      ARE_EQUAL(_testCaseArgsText, test2X2._testCaseArgsText);
      const size_t expectedNumberOfTestCases = 2;
      IS_EMPTY(test2X2._testResults);
      ARE_EQUAL(expectedNumberOfTestCases, test2X2._testResults.capacity());

      // Getters
      ARE_EQUAL(_testName, test2X2.Name());
      ARE_EQUAL("TESTS(" + _testClassName + ")\nTEST2X2(" + _testName + ")", test2X2.FullTestNameValue());
      ARE_EQUAL("(0)", test2X2.FileLineString());
   }

   TEST(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN_1X1_1Arg(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0);
      ARE_EQUAL(tuple<int>(0), testNXN_1X1_1Arg.p_testCaseArgs);

      const TestNXN<TestingTestClass, 1, int, int> testNXN_1X1_2Args(_testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), 0, 0);
      const tuple<int, int> expectedTestCaseArgs1(0, 0);
      ARE_EQUAL(expectedTestCaseArgs1, testNXN_1X1_2Args.p_testCaseArgs);

      const TestNXN<TestingTestClass, 2, const string&, volatile int> testNXN_2X2_4Args(
         _testClassName.c_str(), _testName.c_str(), _testCaseArgsText.c_str(), string(), 100);
      const tuple<string, int> expectedTestCaseArgs2(string(), 100);
      ARE_EQUAL(expectedTestCaseArgs2, testNXN_2X2_4Args.p_testCaseArgs);
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
      struct Test1X1SelfMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
         ZENMOCK_VOID3(RunTestCaseIfNotFilteredOut, size_t, const ZenUnitArgs&, const std::vector<std::string>&)
         ZENMOCK_VOID0_CONST(Exit1IfNonExistentTestCaseNumberSpecified)
         ZENMOCK_NONVOID1_STATIC(ITestCaseNumberGenerator*, ITestCaseNumberGenerator, FactoryNew, bool)

         Test1X1SelfMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>(
               "", // testClassName
               "", // testName
               "", // testCaseArgsText
               0, // test case arg 0
               0 // test case arg 1
               )
            {
               call_ITestCaseNumberGeneratorFactoryNew = BIND_1ARG_ZENMOCK_OBJECT(FactoryNew_ZenMockObject);
            }
      } test1X1SelfMocked;

      ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs, _SelfMocked);

      const ZenUnitArgs args = GetArgs_ZenMockObject_SelfMocked.ReturnRandom();
      test1X1SelfMocked.call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject_SelfMocked);

      ITestCaseNumberGeneratorMock* const testCaseNumberGeneratorMock = new ITestCaseNumberGeneratorMock;
      testCaseNumberGeneratorMock->InitializeMock.Expect();
      testCaseNumberGeneratorMock->NextTestCaseNumberMock.ReturnValues(1, 2, std::numeric_limits<size_t>::max());
      test1X1SelfMocked.FactoryNew_ZenMockObject.Return(testCaseNumberGeneratorMock);

      ZENMOCK_NONVOID0_STATIC(vector<string>, ZenUnit::String, CommaSplitExceptQuotedCommas, _SelfMocked);
      const vector<string> splitTestCaseArgs =
      {
         ZenUnit::Random<string>(),
         ZenUnit::Random<string>(),
         ZenUnit::Random<string>()
      };
      CommaSplitExceptQuotedCommas_ZenMockObject_SelfMocked.Return(splitTestCaseArgs);
      test1X1SelfMocked.call_String_CommaSplitExceptQuotedCommas =
         BIND_0ARG_ZENMOCK_OBJECT(CommaSplitExceptQuotedCommas_ZenMockObject_SelfMocked);

      test1X1SelfMocked.Exit1IfNonExistentTestCaseNumberSpecifiedMock.Expect();

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
      ZEN(GetArgs_ZenMockObject_SelfMocked.CalledOnce());
      ZEN(test1X1SelfMocked.FactoryNew_ZenMockObject.CalledOnceWith(args.randomorder));
      ZEN(testCaseNumberGeneratorMock->InitializeMock.CalledOnceWith(2, N, args));
      ZEN(CommaSplitExceptQuotedCommas_ZenMockObject_SelfMocked.CalledOnce());
      ZEN(testCaseNumberGeneratorMock->NextTestCaseNumberMock.CalledNTimes(3));
      ZEN(test1X1SelfMocked.RunTestCaseIfNotFilteredOutMock.CalledAsFollows(
      {
         { 1, args, splitTestCaseArgs },
         { 2, args, splitTestCaseArgs }
      }));
      ZEN(test1X1SelfMocked.Exit1IfNonExistentTestCaseNumberSpecifiedMock.CalledOnce());
      ARE_EQUAL(1, test1X1SelfMocked._currentTestCaseNumber);
      IS_EMPTY(testResults);
   }

   struct Test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
   {
      ZENMOCK_NONVOID3_CONST(bool, ShouldRunTestCase, const ZenUnitArgs&, const FullTestName&, size_t)
      ZENMOCK_VOID2(RunTestCase, size_t, const std::vector<std::string>&)

      Test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests()
      : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>(
         "", // testClassName
         "", // testName
         "", // testCaseArgsText
         0, // test case arg 0
         0 // test case arg 1
         )
      {
         p_fullTestName.testClassName = nonDefaultTestClassName.c_str();
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
      ZEN(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.CalledOnceWith(
         args, test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.p_fullTestName, testCaseNumber));
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
      ZEN(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.ShouldRunTestCaseMock.CalledOnceWith(
         args, test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.p_fullTestName, testCaseNumber));
      ZEN(test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests.RunTestCaseMock.
         CalledOnceWith(testCaseNumber, splitTestCaseArgs));
   }

   TEST(RunTestCase_DoesSo)
   {
      struct Test1X1SelfMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
         ZENMOCK_VOID2_CONST(PrintTestCaseNumberThenArgsThenArrow, size_t, const vector<string>&)
         ZENMOCK_NONVOID0(TestResult, MockableCallBaseRunTest)
         ZENMOCK_VOID1_CONST(WriteLineOKIfSuccess, const TestResult&)
         Test1X1SelfMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>(
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

      test1X1SelfMocked.WriteLineOKIfSuccessMock.Expect();

      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test1X1SelfMocked.RunTestCase(testCaseNumber, splitTestCaseArgs);
      //
      ZEN(test1X1SelfMocked.PrintTestCaseNumberThenArgsThenArrowMock.CalledOnceWith(testCaseNumber, splitTestCaseArgs));
      ZEN(test1X1SelfMocked.MockableCallBaseRunTestMock.CalledOnce());
      TestResult expectedTestResult;
      expectedTestResult.testCaseNumber = testCaseNumber;
      expectedTestResult.fullTestName.testName = testName.c_str();
      ZEN(test1X1SelfMocked.WriteLineOKIfSuccessMock.CalledOnceWith(expectedTestResult));
      vector<TestResult> expectedResulingTestResults = { expectedTestResult };
      VECTORS_EQUAL(expectedResulingTestResults, test1X1SelfMocked._testResults);
   }

   TEST(Exit1IfNonExistentTestCaseNumberSpecified_NonEmptyTestResults_DoesNothing)
   {
      _testNXN->_testResults.resize(1);
      _testNXN->Exit1IfNonExistentTestCaseNumberSpecified();
   }

   TEST(Exit1IfNonExistentTestCaseNumberSpecified_EmptyTestResults_WritesErrorMessage_Exits1)
   {
      _consoleMock->WriteLineMock.Expect();
      exit_ZenMockObject.Expect();
      IS_EMPTY(_testNXN->_testResults);
      //
      _testNXN->Exit1IfNonExistentTestCaseNumberSpecified();
      //
      const std::string expectedErrorMessage = "\nError: Non-existent test case number specified in -run filter. Exiting with code 1.";
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      ZEN(exit_ZenMockObject.CalledOnceWith(1));
   }

   TEST(ShouldRunTestCase_EmptyRunFilters_ReturnsTrue)
   {
      const ZenUnitArgs args;
      const FullTestName fullTestName;
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool shouldRunTestCase = _testNXN->ShouldRunTestCase(args, fullTestName, testCaseNumber);
      //
      IS_TRUE(shouldRunTestCase);
   }

   TEST2X2(ShouldRunTestCase_NonEmptyRunFilters_ReturnsTrueIfAnyRunFilterMatchesTestClassNameTestNameTestCaseNumber,
      bool anyRunFilterMatchesThisTest, bool expectedReturnValue,
      false, false,
      true, true)
   {
      _callerOfRunFilterMatchesTestCaseMock->ThreeArgAnyMock.Return(anyRunFilterMatchesThisTest);
      ZenUnitArgs args;
      args.runFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      FullTestName fullTestName;
      const string nonDefaultTestClassName = ZenUnit::Random<string>();
      fullTestName.testClassName = nonDefaultTestClassName.c_str();
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool shouldRunTestCase = _testNXN->ShouldRunTestCase(args, fullTestName, testCaseNumber);
      //
      ZEN(_callerOfRunFilterMatchesTestCaseMock->ThreeArgAnyMock.CalledOnceWith(
         args.runFilters, TestNXN<TestingTestClass, N, int>::RunFilterMatchesTestCase, fullTestName, testCaseNumber));
      ARE_EQUAL(expectedReturnValue, shouldRunTestCase);
   }

   TEST(RunFilterMatchesTestCase_ReturnsTrueIfRunFilterMatchesTestCaseNumberAndTestClassNameAndTestName)
   {
      RunFilterMock runFilterMock;
      const bool runFilterMatchesTestCase = runFilterMock.MatchesTestCaseMock.ReturnRandom();
      FullTestName fullTestName;
      const string testClassName = ZenUnit::Random<string>();
      const string testName = ZenUnit::Random<string>();
      fullTestName.testClassName = testClassName.c_str();
      fullTestName.testName = testName.c_str();
      fullTestName.arity = ZenUnit::Random<unsigned char>();
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool returnedRunFilterMatchesTestCase = TestNXN<TestingTestClass, 1, int>::
         RunFilterMatchesTestCase(runFilterMock, fullTestName, testCaseNumber);
      //
      ZEN(runFilterMock.MatchesTestCaseMock.CalledOnceWith(fullTestName.testClassName, fullTestName.testName, testCaseNumber));
      ARE_EQUAL(runFilterMatchesTestCase, returnedRunFilterMatchesTestCase);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULL(_testNXN->_testClass);
      //
      _testNXN->NewTestClass();
      //
      POINTER_WAS_NEWED(_testNXN->_testClass);
      _testNXN->_testClass.reset();
   }

   TEST(Startup_CallsTestClassStartup)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->StartupMock.Expect();
      //
      _testNXN->Startup();
      //
      ZEN(_testNXN->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsRunNXNTestCase)
   {
      struct TestNXN_RunNXNTestCaseMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int>>
      {
         ZENMOCK_VOID2(RunNXNTestCase, TestingTestClass*, size_t)
            TestNXN_RunNXNTestCaseMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int>>("", "", "", 0) {}
      } testNXN_RunNXNTestCaseMocked;

      testNXN_RunNXNTestCaseMocked._testClass = make_unique<TestingTestClass>();
      const size_t currentTestCaseNumber = ZenUnit::Random<size_t>();
      testNXN_RunNXNTestCaseMocked._currentTestCaseNumber = currentTestCaseNumber;
      testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.Expect();
      //
      testNXN_RunNXNTestCaseMocked.TestBody();
      //
      const size_t expectedTestCaseArgsIndex = (currentTestCaseNumber - 1) * N;
      ZEN(testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.CalledOnceWith(
         testNXN_RunNXNTestCaseMocked._testClass.get(), expectedTestCaseArgsIndex));
   }

   TEST(RunNXNTestCase_DoesNothing)
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
      ZEN(_testNXN->_testClass->CleanupMock.CalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorCalled);
      //
      _testNXN->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorCalled);
   }

   TEST3X3(PrintTestCaseNumberThenArgsThenArrow_WritesTestCaseNumberArrow,
      size_t testCaseNumber, size_t expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      1, 1, size_t(0),
      2, 2, size_t(1),
      3, 3, size_t(2))
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteStringsCommaSeparatedMock.Expect();
      const vector<string> splitTestCaseArgs = { "Arg0", "Argument1" };
      //
      _testNXN->PrintTestCaseNumberThenArgsThenArrow(testCaseNumber, splitTestCaseArgs);
      //
      ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { " [", Color::Green },
         { "]", Color::Green }
      }));
      ZEN(_consoleMock->WriteStringsCommaSeparatedMock.CalledOnceWith(
         splitTestCaseArgs, expectedTestCaseArgsPrintingStartIndex, N));
      ZEN(_consoleMock->WriteMock.CalledAsFollows(
      {
         { to_string(expectedTestCaseNumber) },
         { " ("s },
         { ") -> "s }
      }));
   }

   TEST(WriteLineOKIfSuccess_CallsTestResultWriteLineOKIfSuccess)
   {
      TestResultMock testResultMock;
      testResultMock.WriteLineOKIfSuccessMock.Expect();
      //
      _testNXN->WriteLineOKIfSuccess(testResultMock);
      //
      ZEN(testResultMock.WriteLineOKIfSuccessMock.CalledOnceWith(_testNXN->_console.get()));
   }

   RUN_TESTS(TestNXNTests)


   template<typename T>
   TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, T)
   AFACT(Test)
   FACTS(Test1X1)
   FACTS(Test2X2)
   FACTS(Test3X3)
   FACTS(Test4X4)
   FACTS(Test5X5)
   FACTS(Test6X6)
   FACTS(Test7X7)
   FACTS(Test8X8)
   FACTS(Test9X9)
   FACTS(Test10X10)
   EVIDENCE

   TEST(Test) {}
   TEST1X1(Test1X1, int, 0) {}
   TEST2X2(Test2X2, int, int, 0, 0) {}
   TEST3X3(Test3X3, int, int, int, 0, 0, 0) {}
   TEST4X4(Test4X4, int, int, int, int, 0, 0, 0, 0) {}
   TEST5X5(Test5X5, int, int, int, int, int, 0, 0, 0, 0, 0) {}
   TEST6X6(Test6X6, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0) {}
   TEST7X7(Test7X7, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0) {}
   TEST8X8(Test8X8, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0) {}
   TEST9X9(Test9X9, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
   TEST10X10(Test10X10, int, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}

   RUN_TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, int)
}
