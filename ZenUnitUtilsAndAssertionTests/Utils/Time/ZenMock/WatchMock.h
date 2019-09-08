#pragma once

class WatchMock : public Zen::Mock<ZenUnit::Watch>
{
public:
   ZENMOCK_NONVOID0_CONST(string, DateTimeNow)
   ZENMOCK_NONVOID0_CONST(tm, TMNow)
   ZENMOCK_NONVOID0_CONST(long long, SecondsSince1970)
};
