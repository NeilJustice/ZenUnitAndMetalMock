#pragma once

class TestResultFactoryMock : public Metal::Mock<TestResultFactory>
{
public:
   METALMOCK_NONVOID3_CONST(TestResult, MakeConstructorFail,
      const FullTestName&,
      const TestPhaseResult&,
      unsigned short)

   METALMOCK_NONVOID5_CONST(TestResult, MakeStartupFail,
      const FullTestName&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      unsigned short)

   METALMOCK_NONVOID4_CONST(TestResult, MakeConstructorDestructorSuccess,
      const FullTestName&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      unsigned short)

   METALMOCK_NONVOID7_CONST(TestResult, MakeFullTestResult,
      const FullTestName&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      const TestPhaseResult&,
      unsigned short)
};
