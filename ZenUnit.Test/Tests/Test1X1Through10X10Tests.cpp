#include "pch.h"
#include "ZenUnit/Tests/Test1X1ThroughTest10X10.h"
#include "TestNXNUtil.h"

struct StartupCleanupMixin
{
   void Startup() {}
   void Cleanup() {}
};

struct TestingTestClass1X1 : public StartupCleanupMixin
{
   static vector<int> s_calls;
   void Test(int arg)
   {
      s_calls.push_back(arg);
   }
};
vector<int> TestingTestClass1X1::s_calls;

namespace ZenUnit
{
   const char* TestClassName = "TestClassName";
   const char* TestName = "TestName";

   TESTS(Test1X1TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest1By1)
   SPECEND

   CLEANUP
   {
      TestingTestClass1X1::s_calls.clear();
   }

   TEST(Constructor_SetsFields_GettersReturnExpected_RunCallsTest1By1)
   {
      Test1X1<TestingTestClass1X1,
         int,
         int> test1X1_1TestCase(
         TestClassName, TestName, &TestingTestClass1X1::Test,
         "1",
         1);
      AssertTestNXNState(test1X1_1TestCase, 1);

      Test1X1<TestingTestClass1X1,
         int,
         int,
         int> test1X1_2TestCases(
         TestClassName, TestName, &TestingTestClass1X1::Test,
         "1, 2",
         1,
         2);
      AssertTestNXNState(test1X1_2TestCases, 2);

      vector<TestResult> testResults = test1X1_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      ARE_EQUAL(2, TestingTestClass1X1::s_calls.size());
      ARE_EQUAL(1, TestingTestClass1X1::s_calls[0]);
      ARE_EQUAL(2, TestingTestClass1X1::s_calls[1]);
   }

   }; RUN(Test1X1TestTests)
}

struct TestingTestClass2X2 : public StartupCleanupMixin
{
   static vector<tuple<int, string>> s_calls;
   void Test(int arg1, string arg2)
   {
      s_calls.push_back(make_tuple(arg1, arg2));
   }
};
vector<tuple<int, string>> TestingTestClass2X2::s_calls;

namespace ZenUnit
{
   TESTS(Test2X2TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest2X2)
   SPECEND

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
      AssertTestNXNState(test2X2_1TestCase, 1);

      Test2X2<TestingTestClass2X2,
         int, string,
         int, string,
         int, string> test2X2_2TestCases(
         TestClassName, TestName, &TestingTestClass2X2::Test,
         "1, string(), 3, string()",
         1, string(),
         3, string());
      AssertTestNXNState(test2X2_2TestCases, 2);

      vector<TestResult> testResults = test2X2_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, string> expectedFirstCall(1, string());
      tuple<int, string> expectedSecondCall(3, string());
      ARE_EQUAL(2, TestingTestClass2X2::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass2X2::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass2X2::s_calls[1]);
   }

   }; RUN(Test2X2TestTests)
}

struct TestingTestClass3X3 : public StartupCleanupMixin
{
   static vector<tuple<int, int, string>> s_calls;
   void Test(int arg1, int arg2, string arg3)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3));
   }
};
vector<tuple<int, int, string>> TestingTestClass3X3::s_calls;

namespace ZenUnit
{
   TESTS(Test3X3TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest3X3)
   SPECEND

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
      AssertTestNXNState(test3X3_1TestCase, 1);

      Test3X3<TestingTestClass3X3,
         int, int, string,
         int, int, string,
         int, int, string> test3X3_2TestCases(
         TestClassName, TestName, &TestingTestClass3X3::Test,
         "1, 2, string(), 4, 5, string()",
         1, 2, string(),
         4, 5, string());
      AssertTestNXNState(test3X3_2TestCases, 2);

      vector<TestResult> testResults = test3X3_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, string> expectedFirstCall(1, 2, string());
      tuple<int, int, string> expectedSecondCall(4, 5, string());
      ARE_EQUAL(2, TestingTestClass3X3::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass3X3::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass3X3::s_calls[1]);
   }

   }; RUN(Test3X3TestTests)
}

struct TestingTestClass4X4 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, string arg4)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4));
   }
};
vector<tuple<int, int, int, string>> TestingTestClass4X4::s_calls;

namespace ZenUnit
{
   TESTS(Test4X4TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest4X4)
   SPECEND

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
      AssertTestNXNState(test4X4_1TestCase, 1);

      Test4X4<TestingTestClass4X4,
         int, int, int, string,
         int, int, int, string,
         int, int, int, string> test4X4_2TestCases(
         TestClassName, TestName, &TestingTestClass4X4::Test,
         "1, 2, 3, string(), 5, 6, 7, string()",
         1, 2, 3, string(),
         5, 6, 7, string());
      AssertTestNXNState(test4X4_2TestCases, 2);

      vector<TestResult> testResults = test4X4_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, string> expectedFirstCall(1, 2, 3, string());
      tuple<int, int, int, string> expectedSecondCall(5, 6, 7, string());
      ARE_EQUAL(2, TestingTestClass4X4::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass4X4::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass4X4::s_calls[1]);
   }

   }; RUN(Test4X4TestTests)
}

struct TestingTestClass5X5 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, string arg5)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5));
   }
};
vector<tuple<int, int, int, int, string>> TestingTestClass5X5::s_calls;

namespace ZenUnit
{
   TESTS(Test5X5TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest5X5)
   SPECEND

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
      AssertTestNXNState(test5X5_1TestCase, 1);

      Test5X5<TestingTestClass5X5,
         int, int, int, int, string,
         int, int, int, int, string,
         int, int, int, int, string> test5X5_2TestCases(
         TestClassName, TestName, &TestingTestClass5X5::Test,
         "1, 2, 3, 4, string(), 6, 7, 8, 9, string()",
         1, 2, 3, 4, string(),
         6, 7, 8, 9, string());
      AssertTestNXNState(test5X5_2TestCases, 2);

      vector<TestResult> testResults = test5X5_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, string());
      tuple<int, int, int, int, string> expectedSecondCall(6, 7, 8, 9, string());
      ARE_EQUAL(2, TestingTestClass5X5::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass5X5::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass5X5::s_calls[1]);
   }

   }; RUN(Test5X5TestTests)
}

struct TestingTestClass6X6 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, int arg5, string arg6)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5, arg6));
   }
};
vector<tuple<int, int, int, int, int, string>> TestingTestClass6X6::s_calls;

namespace ZenUnit
{
   TESTS(Test6X6TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest6X6)
   SPECEND

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
      AssertTestNXNState(test6X6_1TestCase, 1);

      Test6X6<TestingTestClass6X6,
         int, int, int, int, int, string,
         int, int, int, int, int, string,
         int, int, int, int, int, string> test6X6_2TestCases(
         TestClassName, TestName, &TestingTestClass6X6::Test,
         "1, 2, 3, 4, 5, string(), 7, 8, 9, 10, 11, string()",
         1, 2, 3, 4, 5, string(),
         7, 8, 9, 10, 11, string());
      AssertTestNXNState(test6X6_2TestCases, 2);

      vector<TestResult> testResults = test6X6_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, 5, string());
      tuple<int, int, int, int, int, string> expectedSecondCall(7, 8, 9, 10, 11, string());
      ARE_EQUAL(2, TestingTestClass6X6::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass6X6::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass6X6::s_calls[1]);
   }

   }; RUN(Test6X6TestTests)
}

struct TestingTestClass7X7 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, string arg7)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
   }
};
vector<tuple<int, int, int, int, int, int, string>> TestingTestClass7X7::s_calls;

namespace ZenUnit
{
   TESTS(Test7X7TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest7X7)
   SPECEND

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
      AssertTestNXNState(test7X7_1TestCase, 1);

      Test7X7<TestingTestClass7X7,
         int, int, int, int, int, int, string,
         int, int, int, int, int, int, string,
         int, int, int, int, int, int, string> test7X7_2TestCases(
         TestClassName, TestName, &TestingTestClass7X7::Test,
         "1, 2, 3, 4, 5, 6, string(), 8, 9, 10, 11, 12, 13, string()",
         1, 2, 3, 4, 5, 6, string(),
         8, 9, 10, 11, 12, 13, string());
      AssertTestNXNState(test7X7_2TestCases, 2);

      vector<TestResult> testResults = test7X7_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, 5, 6, string());
      tuple<int, int, int, int, int, int, string> expectedSecondCall(8, 9, 10, 11, 12, 13, string());
      ARE_EQUAL(2, TestingTestClass7X7::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass7X7::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass7X7::s_calls[1]);
   }

   }; RUN(Test7X7TestTests)
}

struct TestingTestClass8X8 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, string eighthArg)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5, arg6, arg7, eighthArg));
   }
};
vector<tuple<int, int, int, int, int, int, int, string>> TestingTestClass8X8::s_calls;

namespace ZenUnit
{
   TESTS(Test8X8TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest8X8)
   SPECEND

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
      AssertTestNXNState(test8X8_1TestCase, 1);

      Test8X8<TestingTestClass8X8,
         int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, string> test8X8_2TestCases(
         TestClassName, TestName, &TestingTestClass8X8::Test,
         "1, 2, 3, 4, 5, 6, 7, string(), 9, 10, 11, 12, 13, 14, 15, string()",
         1, 2, 3, 4, 5, 6, 7, string(),
         9, 10, 11, 12, 13, 14, 15, string());
      AssertTestNXNState(test8X8_2TestCases, 2);

      vector<TestResult> testResults = test8X8_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, 5, 6, 7, string());
      tuple<int, int, int, int, int, int, int, string> expectedSecondCall(9, 10, 11, 12, 13, 14, 15, string());
      ARE_EQUAL(2, TestingTestClass8X8::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass8X8::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass8X8::s_calls[1]);
   }

   }; RUN(Test8X8TestTests)
}

struct TestingTestClass9X9 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int eighthArg, string ninthArg)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5, arg6, arg7, eighthArg, ninthArg));
   }
};
vector<tuple<int, int, int, int, int, int, int, int, string>> TestingTestClass9X9::s_calls;

namespace ZenUnit
{
   TESTS(Test9X9TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest9X9)
   SPECEND

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
      AssertTestNXNState(test9X9_1TestCase, 1);

      Test9X9<TestingTestClass9X9,
         int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, string> test9X9_2TestCases(
         TestClassName, TestName, &TestingTestClass9X9::Test,
         "1, 2, 3, 4, 5, 6, 7, 8, string(), 10, 11, 12, 13, 14, 15, 16, 17, string()",
         1, 2, 3, 4, 5, 6, 7, 8, string(),
         10, 11, 12, 13, 14, 15, 16, 17, string());
      AssertTestNXNState(test9X9_2TestCases, 2);

      vector<TestResult> testResults = test9X9_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, 5, 6, 7, 8, string());
      tuple<int, int, int, int, int, int, int, int, string> expectedSecondCall(10, 11, 12, 13, 14, 15, 16, 17, string());
      ARE_EQUAL(2, TestingTestClass9X9::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass9X9::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass9X9::s_calls[1]);
   }

   }; RUN(Test9X9TestTests)
}

struct TestingTestClass10X10 : public StartupCleanupMixin
{
   static vector<tuple<int, int, int, int, int, int, int, int, int, string>> s_calls;
   void Test(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int eighthArg, int ninthArg, string tenthArg)
   {
      s_calls.push_back(make_tuple(arg1, arg2, arg3, arg4, arg5, arg6, arg7, eighthArg, ninthArg, tenthArg));
   }
};
vector<tuple<int, int, int, int, int, int, int, int, int, string>> TestingTestClass10X10::s_calls;

namespace ZenUnit
{
   TESTS(Test10X10TestTests)
   SPEC(Constructor_SetsFields_GettersReturnExpected_RunCallsTest10X10)
   SPECEND

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
      AssertTestNXNState(test10X10_1TestCase, 1);

      Test10X10<TestingTestClass10X10,
         int, int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, int, string,
         int, int, int, int, int, int, int, int, int, string> test10X10_2TestCases(
         TestClassName, TestName, &TestingTestClass10X10::Test,
         "1, 2, 3, 4, 5, 6, 7, 8, 9, string(), 11, 12, 13, 14, 15, 16, 17, 18, 19, string()",
         1, 2, 3, 4, 5, 6, 7, 8, 9, string(),
         11, 12, 13, 14, 15, 16, 17, 18, 19, string());
      AssertTestNXNState(test10X10_2TestCases, 2);

      vector<TestResult> testResults = test10X10_2TestCases.Run();
      ARE_EQUAL(2, testResults.size());
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[0].fullName);
      ARE_EQUAL(FullName(TestClassName, TestName), testResults[1].fullName);
      ARE_EQUAL(TestOutcome::Success, testResults[0].testOutcome);
      ARE_EQUAL(TestOutcome::Success, testResults[1].testOutcome);
      tuple<int, int, int, int, int, int, int, int, int, string> expectedFirstCall(1, 2, 3, 4, 5, 6, 7, 8, 9, string());
      tuple<int, int, int, int, int, int, int, int, int, string> expectedSecondCall(11, 12, 13, 14, 15, 16, 17, 18, 19, string());
      ARE_EQUAL(2, TestingTestClass10X10::s_calls.size());
      ARE_EQUAL(expectedFirstCall, TestingTestClass10X10::s_calls[0]);
      ARE_EQUAL(expectedSecondCall, TestingTestClass10X10::s_calls[1]);
   }

   }; RUN(Test10X10TestTests)
}
