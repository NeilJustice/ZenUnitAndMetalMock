#include "pch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   AFACT(Constructor_SetsNowFunction)
   AFACT(Start_SetsStartTimeToNow)
   AFACT(Stop_StartNotPreviouslyCalled_Returns0)
   AFACT(Stop_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   EVIDENCE

   Stopwatch _stopwatch;
   ZENMOCK_NONVOID0_STATIC(
      chrono::time_point<chrono::high_resolution_clock>,
      chrono::high_resolution_clock, now)

   STARTUP
   {
      _stopwatch.call_highres_now = BIND_0ARG_ZENMOCK_OBJECT(now_ZenMockObject);
   }

   TEST(Constructor_SetsNowFunction)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch.call_highres_now);
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock>
         nonDefaultTimePoint = chrono::high_resolution_clock::now();
      now_ZenMockObject.Return(nonDefaultTimePoint);
      //
      _stopwatch.Start();
      //
      now_ZenMockObject.CalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
   }

   TEST(Stop_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.Stop());
      ARE_EQUAL(0, _stopwatch.Stop());
   }

   TEST(Stop_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      startTime += chrono::milliseconds(Random<unsigned>());
      const unsigned randomMicrosecondDuration = Random<unsigned>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::microseconds(randomMicrosecondDuration);
      now_ZenMockObject.Return(stopTime);
      _stopwatch._startTime = startTime;
      //
      const unsigned elapsedMicroseconds = _stopwatch.Stop();
      //
      ZEN(now_ZenMockObject.CalledOnce());
      ARE_EQUAL(randomMicrosecondDuration, elapsedMicroseconds);
   }

   RUN_TESTS(StopwatchTests)
}
