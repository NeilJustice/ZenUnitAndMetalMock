#pragma once

struct TestClassResultMock : public Zen::Mock<TestClassResult>
{
   ZENMOCK_VOID1(AddTestResults, const vector<TestResult>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   ZENMOCK_NONVOID0_CONST(unsigned, Milliseconds)
   ZENMOCK_VOID2_CONST(NonMinimalPrintResultLine, const Console*, PrintMode)
   ZENMOCK_VOID3_CONST(PrintTestFailures, const TwoExtraArgsForEacherType*, const Console*, TestFailureNumberer*)
};
