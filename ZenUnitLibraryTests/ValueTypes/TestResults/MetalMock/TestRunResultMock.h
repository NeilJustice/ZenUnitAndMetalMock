#pragma once

class TestRunResultMock : public Metal::Mock<TestRunResult>
{
public:
   METALMOCK_VOID3(AddSkippedTest, const char*, const char*, const char*)
   METALMOCK_VOID2(AddSkippedTestClassNameAndReason, const char*, const char*)
   METALMOCK_VOID1(SetTestClassResults, vector<TestClassResult>)
   METALMOCK_VOID0_CONST(PrintTestFailuresAndSkips)
   METALMOCK_VOID4_CONST(PrintConclusionLines, string_view, size_t, string_view, const ZenUnitArgs&)
   METALMOCK_NONVOID1_CONST(int, DetermineZenUnitExitCode, const ZenUnitArgs&)
   METALMOCK_VOID0(ResetStateExceptForSkips)
};
