#pragma once
#include "ZenUnit/Results/TestClassResult.h"

struct TestClassResultMock : public Zen::Mock<TestClassResult>
{
   ZENMOCK_VOID1(AddTestResults, const vector<TestResult>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   ZENMOCK_NONVOID0_CONST(unsigned, Milliseconds)
   ZENMOCK_VOID2_CONST(NonLaconicPrintResultLine, const Console*, PrintMode)
   ZENMOCK_VOID3_CONST(PrintTestFailures, const ForEacherTwoExtraArgsType*, const Console*, TestFailureNumberer*)
};
