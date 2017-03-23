#pragma once
#include "ZenUnit/Results/TestResult.h"

struct TestResultMock : public Zen::Mock<TestResult>
{
   ZENMOCK_VOID1_CONST(PrintTestOutcome, const Console*)
   ZENMOCK_VOID2_CONST(PrintIfFailure, const Console*, TestFailureNumberer*)
};
