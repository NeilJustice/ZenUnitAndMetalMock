#pragma once

class WatchMock : public Zen::Mock<ZenUnit::Watch>
{
public:
   ZENMOCK_NONVOID0_CONST(string, DateTimeNow)
   ZENMOCK_NONVOID0_CONST(tm, TMNow)
   ZENMOCK_NONVOID0_CONST(unsigned short, SecondsSince1970CastToUnsignedShort)
};
