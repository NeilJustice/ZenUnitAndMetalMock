#pragma once

class TestPhaseRunnerMock : public Zen::Mock<TestPhaseRunner>
{
public:
   using TypedefTestPhaseFunction = void(*)(Test*);
   ZENMOCK_NONVOID3_CONST(TestPhaseResult, RunTestPhase, TypedefTestPhaseFunction, Test*, TestPhase)
};
