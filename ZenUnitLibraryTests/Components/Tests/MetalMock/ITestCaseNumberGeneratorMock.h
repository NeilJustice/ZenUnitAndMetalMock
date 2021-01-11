#pragma once

class ITestCaseNumberGeneratorMock : public Metal::Mock<ITestCaseNumberGenerator>
{
public:
   METALMOCK_VOID2(Initialize, size_t, size_t)
   METALMOCK_NONVOID0(size_t, NextTestCaseNumber)
   METALMOCK_VOID0(ResetTestCaseNumber)
};
