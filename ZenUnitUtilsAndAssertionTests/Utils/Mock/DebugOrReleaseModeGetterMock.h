#pragma once

class DebugOrReleaseGetterMock : public Zen::Mock<DebugOrReleaseGetter>
{
public:
   ZENMOCK_NONVOID0_CONST(string, GetRunningInDebugOrReleaseModeString)
};
