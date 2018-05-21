#pragma once

struct MachineNameGetterMock : public Zen::Mock<MachineNameGetter>
{
   ZENMOCK_NONVOID0_CONST(string, GetMachineName)
};