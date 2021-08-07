#pragma once

class TestClassResultMock : public Metal::Mock<TestClassResult>
{
public:
   METALMOCK_VOID1(AddTestResults, vector<TestResult>)
   METALMOCK_NONVOID1_CONST(string, MicrosecondsToTwoDecimalPlaceMillisecondsString, unsigned)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   METALMOCK_VOID1_CONST(PrintTestClassResultLine, const Console*)
   METALMOCK_VOID3_CONST(PrintTestFailures, const ThreeArgForEacherType*, const Console*, TestFailureNumberer*)
   METALMOCK_NONVOID0_CONST(unsigned, SumOfTestResultMicroseconds)
   METALMOCK_VOID1(ReserveVectorCapacityForNumberOfTestResults, size_t)
};
