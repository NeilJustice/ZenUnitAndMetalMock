#pragma once
#include "ZenUnit/Utils/Time/Stopwatch.h"

struct StopwatchMock : public Zen::Mock<ZenUnit::Stopwatch>
{
   ZENMOCK_VOID0(Start)
   ZENMOCK_NONVOID0(unsigned, Stop)
};
