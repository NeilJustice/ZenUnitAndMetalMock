#pragma once

struct TestClassResultMock : public Zen::Mock<TestClassResult>
{
   ZENMOCK_VOID1(AddTestResults, const vector<TestResult>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   ZENMOCK_NONVOID0_CONST(unsigned, SumOfTestResultMicroseconds)
   ZENMOCK_VOID1_CONST(PrintTestClassResultLine, const Console*)
   ZENMOCK_VOID3_CONST(PrintTestFailures, const ThreeArgForEacherType*, const Console*, TestFailureNumberer*)
   ZENMOCK_NONVOID1_CONST(string, MicrosecondsToThreeDecimalPlaceMillisecondsString, unsigned)
};
