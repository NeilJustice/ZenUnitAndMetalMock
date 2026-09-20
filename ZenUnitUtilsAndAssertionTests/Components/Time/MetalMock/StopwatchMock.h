#pragma once

class StopwatchMock : public Metal::Mock<ZenUnit::Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(unsigned short, GetElapsedMillisecondsThenResetStopwatch)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
