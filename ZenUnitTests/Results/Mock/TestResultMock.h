#pragma once

struct TestResultMock : public Zen::Mock<TestResult>
{
   ZENMOCK_VOID2_CONST(NonMinimalWriteLineOKIfSuccess, const Console*, PrintMode)
   ZENMOCK_VOID2_CONST(PrintIfFailure, const Console*, TestFailureNumberer*)
};
