#pragma once

class TestResultFactoryMock : public Zen::Mock<TestResultFactory>
{
public:
   ZENMOCK_NONVOID2_CONST(TestResult, MakeConstructorFail, const FullTestName&, const CallResult&)
   ZENMOCK_NONVOID4_CONST(TestResult, MakeStartupFail, const FullTestName&, const CallResult&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID3_CONST(TestResult, MakeCtorDtorSuccess, const FullTestName&, const CallResult&, const CallResult&)
   ZENMOCK_NONVOID6_CONST(TestResult, MakeFullTestResult,
      const FullTestName&, const CallResult&, const CallResult&, const CallResult&, const CallResult&, const CallResult&)
};
