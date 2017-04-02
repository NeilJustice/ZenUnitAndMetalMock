#pragma once
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Results/TestResultFactory.h"

struct TestResultFactoryMock : public Zen::Mock<TestResultFactory>
{
   ZENMOCK_NONVOID2_CONST(TestResult, ConstructorFail, FullName, const CallResult&)
   ZENMOCK_NONVOID4_CONST(TestResult, StartupFail, FullName, const CallResult&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID3_CONST(TestResult, CtorDtorSuccess, FullName, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID6_CONST(TestResult, FullCtor,
      FullName, const CallResult&, const CallResult&, const CallResult&, const CallResult&, const CallResult&)
};
