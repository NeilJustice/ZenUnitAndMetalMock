#pragma once
#include "ZenUnit/Results/TestRunResult.h"

struct TestRunResultMock : public Zen::Mock<TestRunResult>
{
   ZENMOCK_VOID3(AddSkippedTest, const char*, const char*, const char*)
   ZENMOCK_VOID2(AddSkippedTestClassNameAndReason, const char*, const char*)
   ZENMOCK_VOID1(SetTestClassResults, vector<TestClassResult>&&)
   ZENMOCK_VOID0_CONST(PrintTestFailuresAndSkips)
   ZENMOCK_VOID3_CONST(PrintClosingLines, size_t, unsigned, const ZenUnitArgs&)
   ZENMOCK_NONVOID1_CONST(int, DetermineExitCode, const ZenUnitArgs&)
   ZENMOCK_VOID0(ResetStateExceptForSkips)
};
