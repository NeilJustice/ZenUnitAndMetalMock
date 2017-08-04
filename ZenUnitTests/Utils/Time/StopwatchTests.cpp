#include "pch.h"
#include "ZenUnit/Utils/Random.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   SPEC(Constructor_SetsNowFunction)
   SPEC(Start_SetsStartTimeToNow)
   SPEC(Stop_StartNotPreviouslyCalled_Returns0)
   SPEC(Stop_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   SPECEND

   Stopwatch _stopwatch;
   ZENMOCK_NONVOID0_STATIC(
      chrono::time_point<chrono::high_resolution_clock>, 
      chrono::high_resolution_clock, now)

   STARTUP
   {
      _stopwatch._highres_now_ZenMockable = ZENBIND0(now_ZenMock);
   }

   TEST(Constructor_SetsNowFunction)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._highres_now_ZenMockable);
      ARE_EQUAL(chrono::time_point<
         chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock>
         nonDefaultTimePoint = chrono::high_resolution_clock::now();
      now_ZenMock.ExpectAndReturn(nonDefaultTimePoint);
      //
      _stopwatch.Start();
      //
      now_ZenMock.AssertCalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
   }

   TEST(Stop_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.Stop());
      ARE_EQUAL(0, _stopwatch.Stop());
   }

   TEST(Stop_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      startTime += chrono::milliseconds(Random<unsigned>());
      unsigned number = Random<unsigned>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::milliseconds(number);
      now_ZenMock.ExpectAndReturn(stopTime);
      _stopwatch._startTime = startTime;
      //
      const unsigned elapsedMilliseconds = _stopwatch.Stop();
      //
      ZEN(now_ZenMock.AssertCalledOnce());
      ARE_EQUAL(number, elapsedMilliseconds);
   }

   }; RUN(StopwatchTests)
}
