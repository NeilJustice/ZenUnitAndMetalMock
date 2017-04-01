#pragma once
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Results/TestResultFactory.h"

struct TestResultFactoryMock : public Zen::Mock<TestResultFactory>
{
   ZENMOCK_NONVOID2_CONST(TestResult, ConstructorFail, const FullName&, const CallResult&)
   ZENMOCK_NONVOID4_CONST(TestResult, StartupFail, const FullName&, const CallResult&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID3_CONST(TestResult, CtorDtorSuccess, const FullName&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID6_CONST(TestResult, FullCtor,
      const FullName&, const CallResult&, const CallResult&, const CallResult&, const CallResult&, const CallResult&)
};
