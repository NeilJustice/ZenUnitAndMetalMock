#pragma once

class StopwatchMock : public Metal::Mock<ZenUnit::Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(unsigned, GetElapsedMicrosecondsThenResetStopwatch)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
