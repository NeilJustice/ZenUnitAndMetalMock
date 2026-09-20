#include "pch.h"

namespace ZenUnit
{
   TESTS(StopwatchTests)
   AFACT(Constructor_SetsNowFunctionToHighResolutionClockNow)
   AFACT(Start_SetsStartTimeToNow)
   AFACT(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
   AFACT(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   FACTS(StopAndGetElapsedSecondsString_StartPreviouslyCalled_SetsStartTimeToDefaultValue_ReturnsElapsedSecondsString)
   EVIDENCE

   Stopwatch _stopwatch;
   METALMOCK_NONVOID0_STATIC_OR_FREE(chrono::time_point<chrono::high_resolution_clock>, _call_high_resolution_clock_now)

   STARTUP
   {
      _stopwatch._call_high_resolution_clock_now = BIND_0ARG_METALMOCK_OBJECT(_call_high_resolution_clock_nowMock);
   }

   TEST(Constructor_SetsNowFunctionToHighResolutionClockNow)
   {
      Stopwatch stopwatch;
      STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._call_high_resolution_clock_now);
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
   }

   TEST(Start_SetsStartTimeToNow)
   {
      const chrono::time_point<chrono::high_resolution_clock> nonDefaultTimePoint = chrono::high_resolution_clock::now();
      _call_high_resolution_clock_nowMock.Return(nonDefaultTimePoint);
      //
      _stopwatch.Start();
      //
      _call_high_resolution_clock_nowMock.CalledOnce();
      ARE_EQUAL(nonDefaultTimePoint, _stopwatch._startTime);
   }

   TEST(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
   {
      IS_ZERO(_stopwatch.GetElapsedMillisecondsThenResetStopwatch());
      IS_ZERO(_stopwatch.GetElapsedMillisecondsThenResetStopwatch());
   }

   TEST(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
   {
      chrono::time_point<chrono::high_resolution_clock> startDateTime;
      startDateTime += chrono::milliseconds(RandomNon0<unsigned>());
      const unsigned short randomMilliseconds = RandomNon0<unsigned short>();
      const chrono::time_point<chrono::high_resolution_clock> stopTime = startDateTime + chrono::milliseconds(randomMilliseconds);
      _call_high_resolution_clock_nowMock.Return(stopTime);
      _stopwatch._startTime = startDateTime;
      //
      const unsigned short elapsedMilliseconds = _stopwatch.GetElapsedMillisecondsThenResetStopwatch();
      //
      METALMOCK(_call_high_resolution_clock_nowMock.CalledOnce());
      ARE_EQUAL(randomMilliseconds, elapsedMilliseconds);
   }

   TEST2X2(StopAndGetElapsedSecondsString_StartPreviouslyCalled_SetsStartTimeToDefaultValue_ReturnsElapsedSecondsString,
      unsigned short elapsedMilliseconds, const string& expectedReturnValue,
      static_cast<unsigned short>(0), "0.000",
      static_cast<unsigned short>(1), "0.001",
      static_cast<unsigned short>(1234), "1.234",
      numeric_limits<unsigned short>::max(), "65.535")
   {
      chrono::time_point<chrono::high_resolution_clock> startTime;
      const int random1To3MillisecondOffsetFromDefaultStartTimeValue = ZenUnit::RandomBetween<int>(1, 3);
      startTime += chrono::milliseconds(random1To3MillisecondOffsetFromDefaultStartTimeValue);
      _stopwatch._startTime = startTime;

      const chrono::time_point<chrono::high_resolution_clock>
         stopTimeThatIsElapsedMillisecondsAheadOfStartTime = startTime + chrono::milliseconds(elapsedMilliseconds);
      _call_high_resolution_clock_nowMock.Return(stopTimeThatIsElapsedMillisecondsAheadOfStartTime);
      //
      const string elapsedSeconds = _stopwatch.StopAndGetElapsedSeconds();
      //
      METALMOCK(_call_high_resolution_clock_nowMock.CalledOnce());
      ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), _stopwatch._startTime);
      ARE_EQUAL(expectedReturnValue, elapsedSeconds);
   }

   RUN_TESTS(StopwatchTests)
}
