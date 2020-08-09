#pragma once

class ExitCallerMock : public Metal::Mock<ZenUnit::ExitCaller>
{
public:
   METALMOCK_VOID1_CONST(CallExit, int)
};
