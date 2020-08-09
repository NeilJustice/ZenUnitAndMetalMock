#pragma once

class ExitCallerMock : public Zen::Mock<ZenUnit::ExitCaller>
{
public:
   METALMOCK_VOID1_CONST(CallExit, int)
};
