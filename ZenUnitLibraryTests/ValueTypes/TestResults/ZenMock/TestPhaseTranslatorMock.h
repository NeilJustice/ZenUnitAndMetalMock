#pragma once

class TestPhaseTranslatorMock : public Zen::Mock<TestPhaseTranslator>
{
public:
   ZENMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseSuffix, TestPhase)
   ZENMOCK_NONVOID1_CONST(const char*, TestPhaseToTestPhaseName, TestPhase)
};
