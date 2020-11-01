#pragma once

class TestResultFactoryMock : public Metal::Mock<TestResultFactory>
{
public:
   METALMOCK_NONVOID2_CONST(TestResult, MakeConstructorFail, const FullTestName&, const TestPhaseResult&)
   METALMOCK_NONVOID4_CONST(TestResult, MakeStartupFail, const FullTestName&, const TestPhaseResult&, const TestPhaseResult&, const TestPhaseResult&)
   METALMOCK_NONVOID3_CONST(TestResult, MakeConstructorDestructorSuccess, const FullTestName&, const TestPhaseResult&, const TestPhaseResult&)
   METALMOCK_NONVOID6_CONST(TestResult, MakeFullTestResult,
      const FullTestName&, const TestPhaseResult&, const TestPhaseResult&, const TestPhaseResult&, const TestPhaseResult&, const TestPhaseResult&)
};
