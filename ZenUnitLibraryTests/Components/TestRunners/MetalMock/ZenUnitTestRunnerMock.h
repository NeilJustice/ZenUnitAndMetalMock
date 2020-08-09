#pragma once

class ZenUnitTestRunnerMock : public Metal::Mock<ZenUnitTestRunner>
{
public:
   METALMOCK_NONVOID0_CONST(const ZenUnitArgs&, VirtualGetZenUnitArgs)
};
