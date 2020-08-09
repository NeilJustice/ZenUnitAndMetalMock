#pragma once

class TestClassRunnerRunnerMock : public Metal::Mock<TestClassRunnerRunner>
{
public:
   METALMOCK_VOID1(AddTestClassRunner, unique_ptr<TestClassRunner>)
   METALMOCK_VOID1(ApplyTestNameFiltersIfAny, const vector<TestNameFilter>&)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfTestClassesToBeRun)
   METALMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   METALMOCK_NONVOID1(vector<TestClassResult>, RunTestClasses, ZenUnitArgs&)
};
