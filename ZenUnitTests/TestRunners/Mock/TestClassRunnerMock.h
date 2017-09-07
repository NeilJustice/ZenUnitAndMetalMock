#pragma once
#include "ZenUnit/TestRunners/TestClassRunner.h"

struct TestClassRunnerMock : public Zen::Mock<TestClassRunner>
{
   ZENMOCK_NONVOID0_CONST(const char*, TestClassNameForSorting)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID0(TestClassResult, RunTests)
};
