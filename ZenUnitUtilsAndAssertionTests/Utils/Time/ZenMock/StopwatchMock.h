#pragma once

class StopwatchMock : public Zen::Mock<ZenUnit::Stopwatch>
{
public:
   ZENMOCK_VOID0(Start)
   ZENMOCK_NONVOID0(long long, StopAndGetElapsedMicroseconds)
   ZENMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
