#pragma once

class ExitCallerMock : public Zen::Mock<ZenUnit::ExitCaller>
{
public:
   ZENMOCK_VOID1_CONST(CallExit, int)
};
