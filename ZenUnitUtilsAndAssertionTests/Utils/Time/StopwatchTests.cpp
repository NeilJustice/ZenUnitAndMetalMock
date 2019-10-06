#include "pch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   AFACT(Constructor_SetsNowFunction)
   AFACT(Start_SetsStartTimeToNow)
   AFACT(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
   AFACT(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   FACTS(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution)
   EVIDENCE

   Stopwatch _stopwatch;
   ZENMOCK_NONVOID0_STATIC(chrono::time_point<chrono::high_resolution_clock>, chrono::high_resolution_clock, now)

   STARTUP
   {
      _stopwatch._call_high_resolution_clock_now = BIND_0ARG_ZENMOCK_OBJECT(now_ZenMockObject);
   }

   TEST(Constructor_SetsNowFunction)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._call_high_resolution_clock_now);
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock> nonDefaultTimePoint = chrono::high_resolution_clock::now();
      now_ZenMockObject.Return(nonDefaultTimePoint);
      //
      _stopwatch.Start();
      //
      now_ZenMockObject.CalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
   }

   TEST(StopAndGetElapsedMicroseconds_StartNotPreviouslyCalled_Returns0)
   {
      ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMicroseconds());
      ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMicroseconds());
   }

   TEST(StopAndGetElapsedMicroseconds_StartPreviouslyCalled_ReturnsElapsedMicroseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startDateTime;
      startDateTime += chrono::milliseconds(Random<unsigned>());
      const unsigned randomMicrosecondDuration = Random<unsigned>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startDateTime + chrono::microseconds(randomMicrosecondDuration);
      now_ZenMockObject.Return(stopTime);
      _stopwatch._startTime = startDateTime;
      //
      const long long elapsedMicroseconds = _stopwatch.StopAndGetElapsedMicroseconds();
      //
      ZENMOCK(now_ZenMockObject.CalledOnce());
      ARE_EQUAL(randomMicrosecondDuration, elapsedMicroseconds);
   }

   TEST2X2(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution,
      long long elapsedMilliseconds, const string& expectedReturnValue,
      0, "0.000",
      1, "0.001",
      9, "0.009",
      10, "0.010",
      11, "0.011",
      99, "0.099",
      100, "0.100",
      101, "0.101",
      999, "0.999",
      1000, "1.000",
      1001, "1.001",
      1099, "1.099",
      1100, "1.100",
      1101, "1.101",
      1999, "1.999",
      10000, "10.000",
      100000, "100.000",
      1234567, "1234.567")
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      const int random1To3MicrosecondOffsetFromDefaultStartTimeValue = ZenUnit::RandomBetween<int>(1, 3);
      startTime += chrono::microseconds(random1To3MicrosecondOffsetFromDefaultStartTimeValue);
      _stopwatch._startTime = startTime;

      const long long elapsedMicroseconds = elapsedMilliseconds * 1000;
      const chrono::time_point<chrono::high_resolution_clock>
         stopTimeThatIsElapsedMicrosecondsAheadOfStartTime = startTime + chrono::microseconds(elapsedMicroseconds);
      now_ZenMockObject.Return(stopTimeThatIsElapsedMicrosecondsAheadOfStartTime);
      //
      const string elapsedSeconds = _stopwatch.StopAndGetElapsedSeconds();
      //
      ZENMOCK(now_ZenMockObject.CalledOnce());
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), _stopwatch._startTime);
      ARE_EQUAL(expectedReturnValue, elapsedSeconds);
   }

   RUN_TESTS(StopwatchTests)
}
