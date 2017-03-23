#pragma once
#include "ZenUnit/TestRunners/TryCatchCaller.h"

struct TryCatchCallerMock : public Zen::Mock<TryCatchCaller>
{
   using TypedefTestPhaseFunction = void(*)(Test*);
   ZENMOCK_NONVOID3_CONST(CallResult, Call, TypedefTestPhaseFunction, Test*, TestPhase)
};
