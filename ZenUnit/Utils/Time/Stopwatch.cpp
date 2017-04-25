#include "pch.h"
#include "Stopwatch.h"
#include "Utils/AssertTrue.h"

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

   unsigned Stopwatch::Stop()
   {
      if (_startTime == chrono::time_point<chrono::high_resolution_clock>())
      {
         return 0;
      }
      const chrono::time_point<chrono::high_resolution_clock> stopTime = _highres_now_ZenMockable();
      const chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
      const long long elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(elapsedTime).count();
      _startTime = chrono::time_point<chrono::high_resolution_clock>();
      assert_true(elapsedMilliseconds <= numeric_limits<unsigned>::max());
      const unsigned elapsedMillisecondsUnsigned = static_cast<unsigned>(elapsedMilliseconds);
      return elapsedMillisecondsUnsigned;
   }
}
