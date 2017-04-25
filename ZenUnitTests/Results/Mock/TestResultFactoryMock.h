#pragma once
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Results/TestResultFactory.h"

struct TestResultFactoryMock : public Zen::Mock<TestResultFactory>
{
   ZENMOCK_NONVOID2_CONST(TestResult, ConstructorFail, const ClassNameTestName&, const CallResult&)
   ZENMOCK_NONVOID4_CONST(TestResult, StartupFail, const ClassNameTestName&, const CallResult&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID3_CONST(TestResult, CtorDtorSuccess, const ClassNameTestName&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID6_CONST(TestResult, FullCtor,
      const ClassNameTestName&, const CallResult&, const CallResult&, const CallResult&, const CallResult&, const CallResult&)
};
