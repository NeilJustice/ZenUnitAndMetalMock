#pragma once

class TestPhaseRunnerMock : public Zen::Mock<TestPhaseRunner>
{
public:
   using TypedefTestPhaseFunction = void(*)(Test*);
   METALMOCK_NONVOID3_CONST(TestPhaseResult, RunTestPhase, TypedefTestPhaseFunction, Test*, TestPhase)
};
