#pragma once
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"

struct TestClassMultiRunnerMock : public Zen::Mock<MultiTestClassRunner>
{
   ZENMOCK_VOID1(AddTestClassRunner, TestClassRunner*)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestClasses)
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfTestCases)
   ZENMOCK_NONVOID1(vector<TestClassResult>, RunTestClasses, ZenUnitArgs&)
};
