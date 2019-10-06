#include "pch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   AFACT(Constructor_SetsNowFunction)
   AFACT(Start_SetsStartTimeToNow)
   AFACT(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
   AFACT(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   EVIDENCE

   Stopwatch _testPhaseStopwatch;
   ZENMOCK_NONVOID0_STATIC(chrono::time_point<chrono::high_resolution_clock>, chrono::high_resolution_clock, now)

   STARTUP
   {
      _testPhaseStopwatch._call_highres_now = BIND_0ARG_ZENMOCK_OBJECT(now_ZenMockObject);
   }

   TEST(Constructor_SetsNowFunction)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._call_highres_now);
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock>
         nonDefaultTimePoint = chrono::high_resolution_clock::now();
      now_ZenMockObject.Return(nonDefaultTimePoint);
      //
      _testPhaseStopwatch.Start();
      //
      now_ZenMockObject.CalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _testPhaseStopwatch._startTime);
   }

   TEST(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _testPhaseStopwatch.StopAndGetElapsedMicroseconds());
      ARE_EQUAL(0, _testPhaseStopwatch.StopAndGetElapsedMicroseconds());
   }

   TEST(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startDateTime;
      startDateTime += chrono::milliseconds(Random<unsigned>());
      const unsigned randomMicrosecondDuration = Random<unsigned>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startDateTime + chrono::microseconds(randomMicrosecondDuration);
      now_ZenMockObject.Return(stopTime);
      _testPhaseStopwatch._startTime = startDateTime;
      //
      const long long elapsedMicroseconds = _testPhaseStopwatch.StopAndGetElapsedMicroseconds();
      //
      ZENMOCK(now_ZenMockObject.CalledOnce());
      ARE_EQUAL(randomMicrosecondDuration, elapsedMicroseconds);
   }

   RUN_TESTS(StopwatchTests)
}
