#pragma once
#include "ZenUnit/Results/TestClassResult.h"

struct TestClassResultMock : public Zen::Mock<TestClassResult>
{
   ZENMOCK_VOID1(AddTestResults, const vector<TestResult>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   ZENMOCK_NONVOID0_CONST(unsigned, Milliseconds)
   ZENMOCK_VOID1_CONST(PrintResultLine, const Console*)
   ZENMOCK_VOID2_CONST(PrintTestFailures, const Console*, TestFailureNumberer*)
};
