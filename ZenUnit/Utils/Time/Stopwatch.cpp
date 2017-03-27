#include "pch.h"
#include "Stopwatch.h"

namespace ZenUnit
{
   Stopwatch::Stopwatch()
      : _highres_now_ZenMockable(chrono::high_resolution_clock::now)
   {
   }

   void Stopwatch::Start()
   {
      _startTime = _highres_now_ZenMockable();
   }

   long long Stopwatch::StopMilliseconds()
   {
      return Stop(false);
   }

   long long Stopwatch::StopNanoseconds()
   {
      return Stop(true);
   }

   long long Stopwatch::Stop(bool trueNanosecondsFalseMilliseconds)
   {
      if (_startTime == chrono::time_point<chrono::high_resolution_clock>())
      {
         return 0;
      }
      const chrono::time_point<chrono::high_resolution_clock> stopTime = _highres_now_ZenMockable();
      const chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
      long long elapsedNanosOrMillis = 0;
      if (trueNanosecondsFalseMilliseconds)
      {
         elapsedNanosOrMillis = chrono::duration_cast<
            chrono::nanoseconds>(elapsedTime).count();
      }
      else
      {
         elapsedNanosOrMillis = chrono::duration_cast<
            chrono::milliseconds>(elapsedTime).count();
      }
      _startTime = chrono::time_point<chrono::high_resolution_clock>();
      return elapsedNanosOrMillis;
   }
}
