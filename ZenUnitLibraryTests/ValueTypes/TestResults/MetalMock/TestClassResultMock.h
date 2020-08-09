#pragma once

class TestClassResultMock : public Zen::Mock<TestClassResult>
{
public:
   METALMOCK_VOID1(AddTestResults, const vector<TestResult>&)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   METALMOCK_NONVOID0_CONST(long long, SumOfTestResultMicroseconds)
   METALMOCK_VOID1_CONST(PrintTestClassResultLine, const Console*)
   METALMOCK_VOID3_CONST(PrintTestFailures, const ThreeArgForEacherType*, const Console*, TestFailureNumberer*)
   METALMOCK_NONVOID1_CONST(string, MicrosecondsToTwoDecimalPlaceMillisecondsString, long long)
};
