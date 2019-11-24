#pragma once

class ZenUnitTestRunnerMock : public Zen::Mock<ZenUnitTestRunner>
{
public:
   ZENMOCK_NONVOID0_CONST(const ZenUnitArgs&, VirtualGetZenUnitArgs)
};
