#pragma once

class ZenUnitTestRunnerMock : public Zen::Mock<ZenUnitTestRunner>
{
public:
   METALMOCK_NONVOID0_CONST(const ZenUnitArgs&, VirtualGetZenUnitArgs)
};
