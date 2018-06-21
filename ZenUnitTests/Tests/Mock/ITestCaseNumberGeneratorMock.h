#pragma once

class ITestCaseNumberGeneratorMock : public Zen::Mock<ITestCaseNumberGenerator>
{
public:
   ZENMOCK_VOID3(Initialize, size_t, size_t, const ZenUnitArgs&)
   ZENMOCK_NONVOID0(size_t, NextTestCaseNumber)
   ZENMOCK_VOID0(ResetTestCaseNumber)
};
