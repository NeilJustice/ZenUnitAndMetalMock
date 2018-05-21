#pragma once

struct TestResultMock : public Zen::Mock<TestResult>
{
   ZENMOCK_VOID1_CONST(WriteLineOKIfSuccess, const Console*)
   ZENMOCK_VOID2_CONST(PrintIfFailure, const Console*, TestFailureNumberer*)
};
