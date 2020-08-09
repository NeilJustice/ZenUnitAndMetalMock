#pragma once

class WatchMock : public Metal::Mock<ZenUnit::Watch>
{
public:
   METALMOCK_NONVOID0_CONST(string, DateTimeNow)
   METALMOCK_NONVOID0_CONST(tm, TMNow)
   METALMOCK_NONVOID0_CONST(long long, SecondsSince1970)
};
