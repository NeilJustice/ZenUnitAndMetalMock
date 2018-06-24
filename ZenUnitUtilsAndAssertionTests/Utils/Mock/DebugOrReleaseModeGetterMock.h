#pragma once

struct DebugOrReleaseGetterMock : public Zen::Mock<DebugOrReleaseGetter>
{
   ZENMOCK_NONVOID0_CONST(string, GetDebugOrRelease)
};
