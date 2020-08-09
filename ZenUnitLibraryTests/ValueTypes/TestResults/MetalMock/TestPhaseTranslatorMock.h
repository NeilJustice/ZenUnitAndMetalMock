#pragma once

class TestPhaseTranslatorMock : public Metal::Mock<TestPhaseTranslator>
{
public:
   METALMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseSuffix, TestPhase)
   METALMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseName, TestPhase)
};
