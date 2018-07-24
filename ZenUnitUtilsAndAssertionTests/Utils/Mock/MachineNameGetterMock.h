#pragma once

class MachineNameGetterMock : public Zen::Mock<MachineNameGetter>
{
public:
   ZENMOCK_NONVOID0_CONST(string, GetMachineName)
};