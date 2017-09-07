#pragma once
#include "ZenUnit/Results/TestPhaseSuffixer.h"

class TestPhaseSuffixerMock : public Zen::Mock<TestPhaseSuffixer>
{
public:
   ZENMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseSuffix, TestPhase)
};
