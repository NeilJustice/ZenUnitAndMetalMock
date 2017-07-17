#pragma once
#include "ZenUnit/Results/TestResult.h"

struct TestResultMock : public Zen::Mock<TestResult>
{
   ZENMOCK_VOID2_CONST(OptionallyWriteOKIfTestPassed, const Console*, bool)
   ZENMOCK_VOID2_CONST(PrintIfFailure, const Console*, TestFailureNumberer*)
};
