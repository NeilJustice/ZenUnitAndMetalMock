#pragma once

class ITestCaseNumberGeneratorMock : public Metal::Mock<ITestCaseNumberGenerator>
{
public:
   METALMOCK_VOID3(Initialize, size_t, size_t, const ZenUnitArgs&)
   METALMOCK_NONVOID0(size_t, NextTestCaseNumber)
   METALMOCK_VOID0(ResetTestCaseNumber)
};
