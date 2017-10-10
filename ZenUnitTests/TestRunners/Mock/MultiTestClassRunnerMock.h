#pragma once
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"

struct MultiTestClassRunnerMock : public Zen::Mock<MultiTestClassRunner>
{
   ZENMOCK_VOID1(AddTestClassRunner, TestClassRunner*)
   ZENMOCK_VOID1(ApplyRunFiltersIfAny, const vector<string>&)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestClassesToBeRun)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID1(vector<TestClassResult>, RunTestClasses, ZenUnitArgs&)
};
