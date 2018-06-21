#pragma once

class StopwatchMock : public Zen::Mock<ZenUnit::Stopwatch>
{
public:
   ZENMOCK_VOID0(Start)
   ZENMOCK_NONVOID0(unsigned, Stop)
};
