#include "pch.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   SPEC(Constructor_SetsNowFunction)
   SPEC(Start_SetsStartTimeToNow)
   SPEC(StopMilliseconds_StartNotPreviouslyCalled_Returns0)
   SPEC(StopMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   SPEC(StopNanoseconds_StartNotPreviouslyCalled_Returns0)
   SPEC(StopNanoseconds_StartPreviouslyCalled_ReturnsElapsedNanoseconds)
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
      FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._highres_now_ZenMockable);
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

   TEST(StopMilliseconds_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.StopMilliseconds());
      ARE_EQUAL(0, _stopwatch.StopMilliseconds());
   }

   TEST(StopMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      startTime += chrono::milliseconds(100);
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::milliseconds(1234);
      now_ZenMock.ExpectAndReturn(stopTime);
      _stopwatch._startTime = startTime;
      //
      const long long elapsedMilliseconds = _stopwatch.StopMilliseconds();
      //
      ZEN(now_ZenMock.AssertCalledOnce());
      ARE_EQUAL(1234ll, elapsedMilliseconds);
   }

   TEST(StopNanoseconds_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.StopNanoseconds());
      ARE_EQUAL(0, _stopwatch.StopNanoseconds());
   }

   TEST(StopNanoseconds_StartPreviouslyCalled_ReturnsElapsedNanoseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      startTime += chrono::nanoseconds(100);
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::nanoseconds(5678);
      now_ZenMock.ExpectAndReturn(stopTime);
      _stopwatch._startTime = startTime;
      //
      const long long elapsedNanoseconds = _stopwatch.StopNanoseconds();
      //
      ZEN(now_ZenMock.AssertCalledOnce());
      ARE_EQUAL(5678ll, elapsedNanoseconds);
   }

   }; RUN(StopwatchTests)
}
