#pragma once
#include "ZenUnit/Tests/Test.h"

struct TestMock : public Zen::Mock<Test>
{
   TestMock() : Zen::Mock<Test>("", "") {}

   ZENMOCK_NONVOID0_CONST(const char*, Name)
   ZENMOCK_NONVOID0_CONST(string, TestsAndTestLines)
   ZENMOCK_NONVOID0_CONST(string, FileLineString)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_VOID1_CONST(PrintPostTestNameMessage, const Console*)
   ZENMOCK_NONVOID0(vector<TestResult>, Run)
   ZENMOCK_VOID0(NewTestClass)
   ZENMOCK_VOID0(Startup)
   ZENMOCK_VOID0(TestBody)
   ZENMOCK_VOID0(Cleanup)
   ZENMOCK_VOID0(DeleteTestClass)
   ZENMOCK_VOID2_CONST(PrintPostTestCompletionMessage, const Console*, const TestResult&)
};
