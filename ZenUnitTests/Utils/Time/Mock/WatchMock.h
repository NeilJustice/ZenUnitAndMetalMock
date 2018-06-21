#pragma once

struct WatchMock : public Zen::Mock<ZenUnit::Watch>
{
   ZENMOCK_NONVOID0_CONST(string, DateTimeNow)
   ZENMOCK_NONVOID0_CONST(tm, TMNow)
   ZENMOCK_NONVOID0_CONST(unsigned short, SecondsSince1970CastToUnsignedShort)
};
