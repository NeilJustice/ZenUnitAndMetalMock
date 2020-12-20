#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"

struct StartupAndCleanup
{
   void Startup() {}
   void Cleanup() {}
};

namespace ZenUnit
{
   const char* const TestClassName = "Tests";
   const char* const TestName = "Test";

   template<typename TestNXNType>
   void AssertTestNXNState(
      const TestNXNType& testNXN,
      const string& expectedFullTestName,
      size_t expectedNumberOfTestCases)
   {
      ARE_EQUAL("Test", testNXN.Name());
      ARE_EQUAL(expectedFullTestName, testNXN.FullName());
      ARE_EQUAL("(0)", testNXN.FilePathLineNumberString());
      ARE_EQUAL(expectedNumberOfTestCases, testNXN.NumberOfTestCases());
   }

   void AssertTwoExpectedTestResults(const vector<TestResult>& testResults, unsigned char expectedArity)
   {
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullTestName(TestClassName, TestName, expectedArity), testResults[0].fullTestName);
      ARE_EQUAL(FullTestName(TestClassName, TestName, expectedArity), testResults[1].fullTestName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
   }

   template<typename TestingTestClassType, typename TupleCallType>
   void AssertExpectedCalls(const TupleCallType& expectedFirstCall, const TupleCallType& expectedSecondCall)
   {
      const auto& calls = TestingTestClassType::s_calls;
      ARE_EQUAL(2, calls.size());
      CONTAINS_ELEMENT(expectedFirstCall, calls);
      CONTAINS_ELEMENT(expectedSecondCall, calls);
   }

   struct TestingTestClass1X1 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int>> s_calls;
      void Test(size_t zenUnitTestCase, int arg)
      {
         s_calls.emplace_back(zenUnitTestCase, arg);
      }
   };

   struct TestingTestClass2X2 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, string secondArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument);
      }
   };

   struct TestingTestClass3X3 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, string thirdArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument);
      }
   };

   struct TestingTestClass4X4 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, string fourthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument);
      }
   };

   struct TestingTestClass5X5 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, string fifthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument);
      }
   };

   struct TestingTestClass6X6 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, int fifthArgument, string sixthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
      }
   };

   struct TestingTestClass8X8 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, int fifthArgument, int sixthArgument, int seventhArgument, string eigthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument);
      }
   };

   struct TestingTestClass7X7 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, int fifthArgument, int sixthArgument, string seventhArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument);
      }
   };

   struct TestingTestClass9X9 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, int fifthArgument, int sixthArgument, int seventhArgument, int eigthArgument, string ninthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument);
      }
   };

   struct TestingTestClass10X10 : public StartupAndCleanup
   {
      static vector<tuple<size_t, int, int, int, int, int, int, int, int, int, string>> s_calls;
      void Test(size_t zenUnitTestCase, int firstArgument, int secondArgument, int thirdArgument, int fourthArgument, int fifthArgument, int sixthArgument, int seventhArgument, int eigthArgument, int ninthArgument, string tenthArgument)
      {
         s_calls.emplace_back(zenUnitTestCase, firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
      }
   };

   vector<tuple<size_t, int>> TestingTestClass1X1::s_calls;
   vector<tuple<size_t, int, string>> TestingTestClass2X2::s_calls;
   vector<tuple<size_t, int, int, string>> TestingTestClass3X3::s_calls;
   vector<tuple<size_t, int, int, int, string>> TestingTestClass4X4::s_calls;
   vector<tuple<size_t, int, int, int, int, string>> TestingTestClass5X5::s_calls;
   vector<tuple<size_t, int, int, int, int, int, string>> TestingTestClass6X6::s_calls;
   vector<tuple<size_t, int, int, int, int, int, int, int, string>> TestingTestClass8X8::s_calls;
   vector<tuple<size_t, int, int, int, int, int, int, string>> TestingTestClass7X7::s_calls;
   vector<tuple<size_t, int, int, int, int, int, int, int, int, string>> TestingTestClass9X9::s_calls;
   vector<tuple<size_t, int, int, int, int, int, int, int, int, int, string>> TestingTestClass10X10::s_calls;

   TESTS(Test1X1TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest1By1)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass1X1::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest1By1)
   {
      Test1X1<TestingTestClass1X1, int, int> test1X1_1TestCase(
         TestClassName, TestName, &TestingTestClass1X1::Test,
         "1", 1);
      AssertTestNXNState(test1X1_1TestCase, "TESTS(Tests)\nTEST1X1(Test)", 1);

      Test1X1<TestingTestClass1X1, int, int, int> test1X1_2TestCases(
         TestClassName, TestName, &TestingTestClass1X1::Test,
         "10, 20", 10, 20);
      AssertTestNXNState(test1X1_2TestCases, "TESTS(Tests)\nTEST1X1(Test)", 2);

      const vector<TestResult> testResults = test1X1_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 1);
      const tuple<size_t, int> expectedFirstCall(1ull, 10);
      const tuple<size_t, int> expectedSecondCall(2ull, 20);
      AssertExpectedCalls<TestingTestClass1X1>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test1X1TestTests)


   TESTS(Test2X2TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest2X2)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass2X2::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest2X2)
   {
      Test2X2<TestingTestClass2X2,
         int, string,
         int, string> test2X2_1TestCase(
            TestClassName, TestName, &TestingTestClass2X2::Test,
            "1, string()",
            1, string());
      AssertTestNXNState(test2X2_1TestCase, "TESTS(Tests)\nTEST2X2(Test)", 1);

      Test2X2<TestingTestClass2X2,
         int, string,
         int, string,
         int, string> test2X2_2TestCases(
            TestClassName, TestName, &TestingTestClass2X2::Test,
            "10, string(), 30, string()",
            10, string(),
            30, string());
      AssertTestNXNState(test2X2_2TestCases, "TESTS(Tests)\nTEST2X2(Test)", 2);

      const vector<TestResult> testResults = test2X2_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 2);
      const tuple<size_t, int, string> expectedFirstCall(1ull, 10, string());
      const tuple<size_t, int, string> expectedSecondCall(2ull, 30, string());
      AssertExpectedCalls<TestingTestClass2X2>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test2X2TestTests)


   TESTS(Test3X3TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest3X3)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass3X3::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest3X3)
   {
      Test3X3<TestingTestClass3X3,
         int, int, string,
         int, int, string> test3X3_1TestCase(
            TestClassName, TestName, &TestingTestClass3X3::Test,
            "1, 2, string()",
            1, 2, string());
      AssertTestNXNState(test3X3_1TestCase, "TESTS(Tests)\nTEST3X3(Test)", 1);

      Test3X3<TestingTestClass3X3,
         int, int, string,
         int, int, string,
         int, int, string> test3X3_2TestCases(
            TestClassName, TestName, &TestingTestClass3X3::Test,
            "1, 2, string(), 4, 5, string()",
            1, 2, string(),
            4, 5, string());
      AssertTestNXNState(test3X3_2TestCases, "TESTS(Tests)\nTEST3X3(Test)", 2);

      const vector<TestResult> testResults = test3X3_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 3);
      const tuple<size_t, int, int, string> expectedFirstCall(1ull, 1, 2, string());
      const tuple<size_t, int, int, string> expectedSecondCall(2ull, 4, 5, string());
      AssertExpectedCalls<TestingTestClass3X3>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test3X3TestTests)


   TESTS(Test4X4TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest4X4)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass4X4::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest4X4)
   {
      Test4X4<TestingTestClass4X4,
         int, int, int, string,
         int, int, int, string> test4X4_1TestCase(
            TestClassName, TestName, &TestingTestClass4X4::Test,
            "1, 2, 3, string()",
            1, 2, 3, string());
      AssertTestNXNState(test4X4_1TestCase, "TESTS(Tests)\nTEST4X4(Test)", 1);

      Test4X4<TestingTestClass4X4,
         int, int, int, string,
         int, int, int, string,
         int, int, int, string> test4X4_2TestCases(
            TestClassName, TestName, &TestingTestClass4X4::Test,
            "1, 2, 3, string(), 5, 6, 7, string()",
            1, 2, 3, string(),
            5, 6, 7, string());
      AssertTestNXNState(test4X4_2TestCases, "TESTS(Tests)\nTEST4X4(Test)", 2);

      const vector<TestResult> testResults = test4X4_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 4);
      const tuple<size_t, int, int, int, string> expectedFirstCall(1ull, 1, 2, 3, string());
      const tuple<size_t, int, int, int, string> expectedSecondCall(2ull, 5, 6, 7, string());
      AssertExpectedCalls<TestingTestClass4X4>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test4X4TestTests)


   TESTS(Test5X5TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest5X5)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass5X5::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest5X5)
   {
      Test5X5<TestingTestClass5X5,
         int, int, int, int, string,
         int, int, int, int, string> test5X5_1TestCase(
            TestClassName, TestName, &TestingTestClass5X5::Test,
            "1, 2, 3, 4, string()",
            1, 2, 3, 4, string());
      AssertTestNXNState(test5X5_1TestCase, "TESTS(Tests)\nTEST5X5(Test)", 1);

      Test5X5<TestingTestClass5X5,
         int, int, int, int, string,
         int, int, int, int, string,
         int, int, int, int, string> test5X5_2TestCases(
            TestClassName, TestName, &TestingTestClass5X5::Test,
            "1, 2, 3, 4, string(), 6, 7, 8, 9, string()",
            1, 2, 3, 4, string(),
            6, 7, 8, 9, string());
      AssertTestNXNState(test5X5_2TestCases, "TESTS(Tests)\nTEST5X5(Test)", 2);

      const vector<TestResult> testResults = test5X5_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 5);
      const tuple<size_t, int, int, int, int, string> expectedFirstCall(1ull, 1, 2, 3, 4, string());
      const tuple<size_t, int, int, int, int, string> expectedSecondCall(2ull, 6, 7, 8, 9, string());
      AssertExpectedCalls<TestingTestClass5X5>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test5X5TestTests)


   TESTS(Test6X6TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest6X6)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass6X6::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest6X6)
   {
      Test6X6<TestingTestClass6X6,
         int, int, int, int, int, string,
         int, int, int, int, int, string> test6X6_1TestCase(
            TestClassName, TestName, &TestingTestClass6X6::Test,
            "1, 2, 3, 4, 5, string()",
            1, 2, 3, 4, 5, string());
      AssertTestNXNState(test6X6_1TestCase, "TESTS(Tests)\nTEST6X6(Test)", 1);

      Test6X6<TestingTestClass6X6,
         int, int, int, int, int, string,
         int, int, int, int, int, string,
         int, int, int, int, int, string> test6X6_2TestCases(
            TestClassName, TestName, &TestingTestClass6X6::Test,
            "1, 2, 3, 4, 5, string(), 7, 8, 9, 10, 11, string()",
            1, 2, 3, 4, 5, string(),
            7, 8, 9, 10, 11, string());
      AssertTestNXNState(test6X6_2TestCases, "TESTS(Tests)\nTEST6X6(Test)", 2);

      const vector<TestResult> testResults = test6X6_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 6);
      const tuple<size_t, int, int, int, int, int, string> expectedFirstCall(1ull, 1, 2, 3, 4, 5, string());
      const tuple<size_t, int, int, int, int, int, string> expectedSecondCall(2ull, 7, 8, 9, 10, 11, string());
      AssertExpectedCalls<TestingTestClass6X6>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test6X6TestTests)


   TESTS(Test7X7TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest7X7)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass7X7::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest7X7)
   {
      Test7X7<TestingTestClass7X7,
         int, int, int, int, int, int, string,
         int, int, int, int, int, int, string> test7X7_1TestCase(
            TestClassName, TestName, &TestingTestClass7X7::Test,
            "1, 2, 3, 4, 5, 6, string()",
            1, 2, 3, 4, 5, 6, string());
      AssertTestNXNState(test7X7_1TestCase, "TESTS(Tests)\nTEST7X7(Test)", 1);

      Test7X7<TestingTestClass7X7,
         int, int, int, int, int, int, string,
         int, int, int, int, int, int, string,
         int, int, int, int, int, int, string> test7X7_2TestCases(
            TestClassName, TestName, &TestingTestClass7X7::Test,
            "1, 2, 3, 4, 5, 6, string(), 8, 9, 10, 11, 12, 13, string()",
            1, 2, 3, 4, 5, 6, string(),
            8, 9, 10, 11, 12, 13, string());
      AssertTestNXNState(test7X7_2TestCases, "TESTS(Tests)\nTEST7X7(Test)", 2);

      const vector<TestResult> testResults = test7X7_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 7);
      const tuple<size_t, int, int, int, int, int, int, string> expectedFirstCall(1ull, 1, 2, 3, 4, 5, 6, string());
      const tuple<size_t, int, int, int, int, int, int, string> expectedSecondCall(2ull, 8, 9, 10, 11, 12, 13, string());
      AssertExpectedCalls<TestingTestClass7X7>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test7X7TestTests)


   TESTS(Test8X8TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest8X8)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass8X8::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest8X8)
   {
      Test8X8<TestingTestClass8X8,
         int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, string> test8X8_1TestCase(
            TestClassName, TestName, &TestingTestClass8X8::Test,
            "1, 2, 3, 4, 5, 6, 7, string()",
            1, 2, 3, 4, 5, 6, 7, string());
      AssertTestNXNState(test8X8_1TestCase, "TESTS(Tests)\nTEST8X8(Test)", 1);

      Test8X8<TestingTestClass8X8,
         int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, string> test8X8_2TestCases(
            TestClassName, TestName, &TestingTestClass8X8::Test,
            "1, 2, 3, 4, 5, 6, 7, string(), 9, 10, 11, 12, 13, 14, 15, string()",
            1, 2, 3, 4, 5, 6, 7, string(),
            9, 10, 11, 12, 13, 14, 15, string());
      AssertTestNXNState(test8X8_2TestCases, "TESTS(Tests)\nTEST8X8(Test)", 2);

      const vector<TestResult> testResults = test8X8_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 8);
      const tuple<size_t, int, int, int, int, int, int, int, string> expectedFirstCall(1ull, 1, 2, 3, 4, 5, 6, 7, string());
      const tuple<size_t, int, int, int, int, int, int, int, string> expectedSecondCall(2ull, 9, 10, 11, 12, 13, 14, 15, string());
      AssertExpectedCalls<TestingTestClass8X8>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test8X8TestTests)


   TESTS(Test9X9TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest9X9)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass9X9::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest9X9)
   {
      Test9X9<TestingTestClass9X9,
         int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, string> test9X9_1TestCase(
            TestClassName, TestName, &TestingTestClass9X9::Test,
            "1, 2, 3, 4, 5, 6, 7, 8, string()",
            1, 2, 3, 4, 5, 6, 7, 8, string());
      AssertTestNXNState(test9X9_1TestCase, "TESTS(Tests)\nTEST9X9(Test)", 1);

      Test9X9<TestingTestClass9X9,
         int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, string> test9X9_2TestCases(
            TestClassName, TestName, &TestingTestClass9X9::Test,
            "1, 2, 3, 4, 5, 6, 7, 8, string(), 10, 11, 12, 13, 14, 15, 16, 17, string()",
            1, 2, 3, 4, 5, 6, 7, 8, string(),
            10, 11, 12, 13, 14, 15, 16, 17, string());
      AssertTestNXNState(test9X9_2TestCases, "TESTS(Tests)\nTEST9X9(Test)", 2);

      const vector<TestResult> testResults = test9X9_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 9);
      const tuple<size_t, int, int, int, int, int, int, int, int, string> expectedFirstCall(
         1ull, 1, 2, 3, 4, 5, 6, 7, 8, string());
      const tuple<size_t, int, int, int, int, int, int, int, int, string> expectedSecondCall(
         2ull, 10, 11, 12, 13, 14, 15, 16, 17, string());
      AssertExpectedCalls<TestingTestClass9X9>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test9X9TestTests)


   TESTS(Test10X10TestTests)
   AFACT(Constructor_SetsFields_GettersReturnExpected_RunCallsTest10X10)
   EVIDENCE

   CLEANUP
   {
      TestingTestClass10X10::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest10X10)
   {
      Test10X10<TestingTestClass10X10,
         int, int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, int, string> test10X10_1TestCase(
            TestClassName, TestName, &TestingTestClass10X10::Test,
            "1, 2, 3, 4, 5, 6, 7, 8, 9, string()",
            1, 2, 3, 4, 5, 6, 7, 8, 9, string());
      AssertTestNXNState(test10X10_1TestCase, "TESTS(Tests)\nTEST10X10(Test)", 1);

      Test10X10<TestingTestClass10X10,
         int, int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, int, string> test10X10_2TestCases(
            TestClassName, TestName, &TestingTestClass10X10::Test,
            "1, 2, 3, 4, 5, 6, 7, 8, 9, string(), 11, 12, 13, 14, 15, 16, 17, 18, 19, string()",
            1, 2, 3, 4, 5, 6, 7, 8, 9, string(),
            11, 12, 13, 14, 15, 16, 17, 18, 19, string());
      AssertTestNXNState(test10X10_2TestCases, "TESTS(Tests)\nTEST10X10(Test)", 2);

      const vector<TestResult> testResults = test10X10_2TestCases.RunTest();
      AssertTwoExpectedTestResults(testResults, 10);
      const tuple<size_t, int, int, int, int, int, int, int, int, int, string> expectedFirstCall(
         1ull, 1, 2, 3, 4, 5, 6, 7, 8, 9, string());
      const tuple<size_t, int, int, int, int, int, int, int, int, int, string> expectedSecondCall(
         2ull, 11, 12, 13, 14, 15, 16, 17, 18, 19, string());
      AssertExpectedCalls<TestingTestClass10X10>(expectedFirstCall, expectedSecondCall);
   }

   RUN_TESTS(Test10X10TestTests)
}
