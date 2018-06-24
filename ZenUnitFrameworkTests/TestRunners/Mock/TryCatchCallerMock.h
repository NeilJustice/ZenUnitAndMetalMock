#pragma once

class TryCatchCallerMock : public Zen::Mock<TryCatchCaller>
{
public:
   using TypedefTestPhaseFunction = void(*)(Test*);
   ZENMOCK_NONVOID3_CONST(CallResult, Call, TypedefTestPhaseFunction, Test*, TestPhase)
};
