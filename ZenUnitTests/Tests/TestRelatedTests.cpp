#include "pch.h"
#include "ZenUnitTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Random/RandomZenUnitArgs.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ThreeArgAnyerMock.h"

namespace ZenUnit
{
   struct TestingDerivedTestClassType : public TestClass<TestingDerivedTestClassType>
   {
      static bool s_allNXNTestsRegistered;
   };

   bool TestingDerivedTestClassType::s_allNXNTestsRegistered = false;

   TESTS(TestClassTests)
   AFACT(DefaultConstructor_DoesNotThrow)
   AFACT(Startup_DoesNotThrow)
   AFACT(Cleanup_DoesNotThrow)
   AFACT(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   EVIDENCE

   TestClass _testClass;

   CLEANUP
   {
      TestingDerivedTestClassType::s_allNXNTestsRegistered = false;
   }

   TEST(DefaultConstructor_DoesNotThrow)
   {
      const TestClass testClass{};
   }

   TEST(Startup_DoesNotThrow)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNotThrow)
   {
      _testClass.Cleanup();
   }

   TEST(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   {
      IS_FALSE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
      {
         const TestClass<TestingDerivedTestClassType> testClass{};
      }
      IS_TRUE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
   }

   RUN_TESTS(TestClassTests)


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
   FACTS(PrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow)
   AFACT(WriteLineOKIfSuccess_CallsTestResultWriteLineOKIfSuccess)
   EVIDENCE

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   ConsoleMock* _consoleMock = nullptr;
   using ThreeArgAnyerMockType = ThreeArgAnyerMock<
      std::vector<RunFilter>, bool(*)(const RunFilter&, const FullTestName&, unsigned), const FullTestName&, unsigned>;
   ThreeArgAnyerMockType* _threeArgAnyerMock = nullptr;
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();
   const string TestCaseArgsText = Random<string>();
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)
   ZENMOCK_VOID1_FREE(exit, int)

   STARTUP
   {
      _testNXN = make_unique<TestNXN<TestingTestClass, N, int>>("", "", "", 0);
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
      _testNXN->_threeArgAnyer.reset(_threeArgAnyerMock = new ThreeArgAnyerMockType);
      _testNXN->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
      _testNXN->call_exit = ZENMOCK_BIND1(exit_ZenMock);
   }

   TEST(Constructor_NewsComponents_SetsFields_MakesGettersReturnExpected)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> test2X2(
         TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0);
      //

      // Fields
      POINTER_WAS_NEWED(test2X2._console);
      POINTER_WAS_NEWED(test2X2._threeArgAnyer);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, test2X2.call_TestRunner_GetArgs);
      STD_FUNCTION_TARGETS(::exit, test2X2.call_exit);
      STD_FUNCTION_TARGETS(String::CommaSplitExceptQuotedCommas, test2X2.call_String_CommaSplitExceptQuotedCommas);
      IS_NULL(test2X2._testClass);
      ARE_EQUAL(0, test2X2._testCaseArgsIndex);
      ARE_EQUAL(TestCaseArgsText, test2X2._testCaseArgsText);
      const size_t expectedNumberOfTestCases = 2;
      IS_EMPTY(test2X2._testResults);
      ARE_EQUAL(expectedNumberOfTestCases, test2X2._testResults.capacity());

      // Getters
      ARE_EQUAL(TestName, test2X2.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST2X2(" + TestName + ")", test2X2.FullTestNameValue());
      ARE_EQUAL("(0)", test2X2.FileLineString());
   }

   TEST(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN_1X1_1Arg(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0);
      ARE_EQUAL(tuple<int>(0), testNXN_1X1_1Arg.p_testCaseArgs);

      const TestNXN<TestingTestClass, 1, int, int> testNXN_1X1_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      const tuple<int, int> expectedTestCaseArgs1(0, 0);
      ARE_EQUAL(expectedTestCaseArgs1, testNXN_1X1_2Args.p_testCaseArgs);

      const TestNXN<TestingTestClass, 2, const string&, volatile int> testNXN_2X2_4Args(
         TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), string(), 100);
      const tuple<string, int> expectedTestCaseArgs2(string(), 100);
      ARE_EQUAL(expectedTestCaseArgs2, testNXN_2X2_4Args.p_testCaseArgs);
   }

   TEST(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   {
      const TestNXN<TestingTestClass, 1, int>
         test1X1(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0);
      ARE_EQUAL(1, test1X1.NumberOfTestCases());

      const TestNXN<TestingTestClass, 1, int, int>
         test1X1_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(2, test1X1_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int>
         test2X2_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(1, test2X2_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int, int, int>
         test2X2_4Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0);
      ARE_EQUAL(2, test2X2_4Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 3, int, int, int, int, int, int, int, int, int>
         test3X3_9Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0, 0, 0, 0, 0, 0);
      ARE_EQUAL(3, test3X3_9Args.NumberOfTestCases());
   }

   TEST(RunTest_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   {
      struct Test1X1SelfMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
         ZENMOCK_VOID3(RunTestCaseIfNotFilteredOut, unsigned, const ZenUnitArgs&, const std::vector<std::string>&)
         ZENMOCK_VOID0_CONST(Exit1IfNonExistentTestCaseNumberSpecified)

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

      ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs, _SelfMocked);

      const ZenUnitArgs args = GetArgs_ZenMock_SelfMocked.ReturnRandom();
      test1X1SelfMocked.call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock_SelfMocked);

      ZENMOCK_NONVOID0_STATIC(vector<string>, ZenUnit::String, CommaSplitExceptQuotedCommas, _SelfMocked);
      const vector<string> splitTestCaseArgs = { ZenUnit::Random<string>(), ZenUnit::Random<string>(), ZenUnit::Random<string>() };
      CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.Return(splitTestCaseArgs);
      test1X1SelfMocked.call_String_CommaSplitExceptQuotedCommas = ZENMOCK_BIND0(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked);

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
      ZEN(GetArgs_ZenMock_SelfMocked.CalledOnce());
      ZEN(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.CalledOnce());
      ZEN(test1X1SelfMocked.RunTestCaseIfNotFilteredOutMock.CalledAsFollows(
      {
         { 1, args, splitTestCaseArgs },
         { 2, args, splitTestCaseArgs }
      }));
      ZEN(test1X1SelfMocked.Exit1IfNonExistentTestCaseNumberSpecifiedMock.CalledOnce());
      ARE_EQUAL(0, test1X1SelfMocked._testCaseArgsIndex);
      VECTORS_EQUAL(vector<TestResult>(), testResults);
   }

   struct Test1X1SelfMocked_RunTestCaseIfNotFilteredOutTests : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
   {
      ZENMOCK_NONVOID3_CONST(bool, ShouldRunTestCase, const ZenUnitArgs&, const FullTestName&, unsigned)
      ZENMOCK_VOID2(RunTestCase, unsigned, const std::vector<std::string>&)

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

      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
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

      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
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
         ZENMOCK_VOID2_CONST(PrintTestCaseNumberArgsThenArrow, unsigned, const vector<string>&)
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

      test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.Expect();

      TestResult testResult;
      const string testName = ZenUnit::Random<string>();
      testResult.fullTestName.testName = testName.c_str();
      test1X1SelfMocked.MockableCallBaseRunTestMock.Return(testResult);

      test1X1SelfMocked.WriteLineOKIfSuccessMock.Expect();

      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
      const vector<string> splitTestCaseArgs = ZenUnit::RandomVector<string>();
      //
      test1X1SelfMocked.RunTestCase(testCaseNumber, splitTestCaseArgs);
      //
      ZEN(test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.CalledOnceWith(testCaseNumber, splitTestCaseArgs));
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
      exit_ZenMock.Expect();
      IS_EMPTY(_testNXN->_testResults);
      //
      _testNXN->Exit1IfNonExistentTestCaseNumberSpecified();
      //
      const std::string expectedErrorMessage = "\nError: Non-existent test case number specified in -run filter. Exiting with code 1.";
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      ZEN(exit_ZenMock.CalledOnceWith(1));
   }

   TEST(ShouldRunTestCase_EmptyRunFilters_ReturnsTrue)
   {
      const ZenUnitArgs args;
      const FullTestName fullTestName;
      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
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
      _threeArgAnyerMock->ThreeArgAnyMock.Return(anyRunFilterMatchesThisTest);
      ZenUnitArgs args;
      args.runFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      FullTestName fullTestName;
      const string nonDefaultTestClassName = ZenUnit::Random<string>();
      fullTestName.testClassName = nonDefaultTestClassName.c_str();
      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
      //
      const bool shouldRunTestCase = _testNXN->ShouldRunTestCase(args, fullTestName, testCaseNumber);
      //
      ZEN(_threeArgAnyerMock->ThreeArgAnyMock.CalledOnceWith(
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
      const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
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
      testNXN_RunNXNTestCaseMocked._testCaseArgsIndex = 1;
      testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.Expect();
      //
      testNXN_RunNXNTestCaseMocked.TestBody();
      //
      ZEN(testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.CalledOnceWith(
         testNXN_RunNXNTestCaseMocked._testClass.get(), testNXN_RunNXNTestCaseMocked._testCaseArgsIndex));
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

   TEST3X3(PrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow,
      unsigned testCaseNumber, int expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      static_cast<unsigned>(1), 1, size_t(0),
      static_cast<unsigned>(2), 2, size_t(1),
      static_cast<unsigned>(3), 3, size_t(2))
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->WriteStringsCommaSeparatedMock.Expect();
      const vector<string> splitTestCaseArgs = { "Arg0", "Argument1" };
      //
      _testNXN->PrintTestCaseNumberArgsThenArrow(testCaseNumber, splitTestCaseArgs);
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


   TESTS(TestTests)
   AFACT(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   FACTS(BaseRunTest_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   FACTS(BaseRunTest_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   AFACT(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   AFACT(WritePostTestNameMessage_DoesNothing)
   AFACT(PrintPostTestCompletionMessage_DoesNothing)
   AFACT(StaticCallNewTestClass_CallsNewTestClass)
   AFACT(StaticCallStartup_CallsStartup)
   AFACT(StaticTestBody_CallsTestBody)
   AFACT(StaticCallCleanup_CallsCleanup)
   AFACT(StaticCallDeleteTestClass_CallsDeleteTestClass)
   AFACT(PseudoAbstractFunctions_DoNothingOrReturn0)
   EVIDENCE

   unique_ptr<Test> _test;
   TryCatchCallerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   TestMock _testMock;

   STARTUP
   {
      _test = make_unique<Test>("", "", static_cast<unsigned char>(0));
      _test->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _test->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   {
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      //
      Test test(testClassName.c_str(), testName.c_str(), 0);
      POINTER_WAS_NEWED(test._tryCatchCaller);
      POINTER_WAS_NEWED(test._testResultFactory);
      ARE_EQUAL(FileLine(), test.p_fileLine);

      const char* const testNameValue = test.Name();
      ARE_EQUAL(testName.c_str(), testNameValue);

      const string fullTestName = test.FullTestNameValue();
      ARE_EQUAL(fullTestName, test.p_fullTestName.Value());

      test.p_fileLine = FileLine("FilePath", 1);
      ARE_EQUAL(test.p_fileLine.ToString(), test.FileLineString());
   }

   TEST(WritePostTestNameMessage_DoesNothing)
   {
      _test->WritePostTestNameMessage(nullptr);
      _test->WritePostTestNameMessage(nullptr);
   }

   TEST(PrintPostTestCompletionMessage_DoesNothing)
   {
      TestResultMock testResultMock;
      _test->WritePostTestCompletionMessage(nullptr, testResultMock);
      _test->WritePostTestCompletionMessage(nullptr, testResultMock);
   }

   static CallResult CallResultWithOutcome(TestOutcome testOutcome)
   {
      CallResult callResult;
      callResult.testOutcome = testOutcome;
      return callResult;
   }

   TEST1X1(BaseRunTest_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail,
      TestOutcome constructorOutcome, TestOutcome::Anomaly, TestOutcome::Exception)
   {
      const CallResult constructorFailCallResult = CallResultWithOutcome(constructorOutcome);
      _tryCatchCallerMock->CallMock.Return(constructorFailCallResult);

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->ConstructorFailMock.Return(constructorFailTestResult);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledOnceWith(
         &Test::CallNewTestClass, _test.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.CalledOnceWith(
         _test->p_fullTestName, constructorFailCallResult));
      ARE_EQUAL(constructorFailTestResult, testResult);
   }

   TEST1X1(BaseRunTest_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail,
      TestOutcome startupOutcome,
      TestOutcome::Anomaly,
      TestOutcome::Exception)
   {
      const CallResult constructorSuccessCallResult = CallResultWithOutcome(TestOutcome::Success);
      const CallResult startupFailCallResult = CallResultWithOutcome(startupOutcome);
      const CallResult destructorCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.ReturnValues(constructorSuccessCallResult, startupFailCallResult, destructorCallResult);

      const TestResult startupFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->StartupFailMock.Return(startupFailTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->p_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->StartupFailMock.CalledOnceWith(
         _test->p_fullTestName, constructorSuccessCallResult, startupFailCallResult, destructorCallResult));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const CallResult successCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.Return(successCallResult);

      const TestResult sixArgTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->FullCtorMock.Return(sixArgTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->p_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallTestBody, _test.get(), TestPhase::TestBody },
         { &Test::CallCleanup, _test.get(), TestPhase::Cleanup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->FullCtorMock.CalledOnceWith(
         _test->p_fullTestName,
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success)));
      ARE_EQUAL(testResult, sixArgTestResult);
   }

   TEST(StaticCallNewTestClass_CallsNewTestClass)
   {
      _testMock.NewTestClassMock.Expect();
      //
      Test::CallNewTestClass(&_testMock);
      //
      ZEN(_testMock.NewTestClassMock.CalledOnce());
   }

   TEST(StaticCallStartup_CallsStartup)
   {
      _testMock.StartupMock.Expect();
      //
      Test::CallStartup(&_testMock);
      //
      ZEN(_testMock.StartupMock.CalledOnce());
   }

   TEST(StaticTestBody_CallsTestBody)
   {
      _testMock.TestBodyMock.Expect();
      //
      Test::CallTestBody(&_testMock);
      //
      ZEN(_testMock.TestBodyMock.CalledOnce());
   }

   TEST(StaticCallCleanup_CallsCleanup)
   {
      _testMock.CleanupMock.Expect();
      //
      Test::CallCleanup(&_testMock);
      //
      ZEN(_testMock.CleanupMock.CalledOnce());
   }

   TEST(StaticCallDeleteTestClass_CallsDeleteTestClass)
   {
      _testMock.DeleteTestClassMock.Expect();
      //
      Test::CallDeleteTestClass(&_testMock);
      //
      ZEN(_testMock.DeleteTestClassMock.CalledOnce());
   }

   TEST(PseudoAbstractFunctions_DoNothingOrReturn0)
   {
      Test test("", "", 0);
      ARE_EQUAL(0, test.NumberOfTestCases());
      IS_EMPTY(test.RunTest());
      test.NewTestClass();
      test.Startup();
      test.TestBody();
      test.Cleanup();
      test.DeleteTestClass();
   }

   RUN_TESTS(TestTests)
}
