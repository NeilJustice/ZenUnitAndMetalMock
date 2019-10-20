#pragma once

class TestClassRunnerRunnerMock : public Zen::Mock<TestClassRunnerRunner>
{
public:
   ZENMOCK_VOID1(AddTestClassRunner, unique_ptr<TestClassRunner>)
   ZENMOCK_VOID1(ApplyRunFiltersIfAny, const vector<RunFilter>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestClassesToBeRun)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID1(vector<TestClassResult>, RunTestClasses, ZenUnitArgs&)
};
