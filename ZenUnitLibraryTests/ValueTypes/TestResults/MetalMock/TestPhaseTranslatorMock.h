#pragma once

class TestPhaseTranslatorMock : public Zen::Mock<TestPhaseTranslator>
{
public:
   METALMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseSuffix, TestPhase)
   METALMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseName, TestPhase)
};
