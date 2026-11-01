#pragma once

class StopwatchMock : public Metal::Mock<ZenUnit::Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(unsigned short, StopAndGetElapsedMilliseconds)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSecondsString)
};
