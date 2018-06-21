#pragma once

class TestResultMock : public Zen::Mock<TestResult>
{
public:
   ZENMOCK_VOID1_CONST(WriteLineOKIfSuccess, const Console*)
   ZENMOCK_VOID2_CONST(PrintIfFailure, const Console*, TestFailureNumberer*)
};
