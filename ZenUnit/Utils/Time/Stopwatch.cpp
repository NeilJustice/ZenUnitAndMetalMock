#include "pch.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   Stopwatch::Stopwatch()
      : _highres_now_ZenMockable(std::chrono::high_resolution_clock::now)
   {
   }

   void Stopwatch::Start()
   {
      _startTime = _highres_now_ZenMockable();
   }

   unsigned Stopwatch::Stop()
   {
      if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
      {
         return 0;
      }
      const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = _highres_now_ZenMockable();
      const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
      const long long elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();
      _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
      assert_true(elapsedMilliseconds <= std::numeric_limits<unsigned>::max());
      const unsigned elapsedMillisecondsUnsigned = static_cast<unsigned>(elapsedMilliseconds);
      return elapsedMillisecondsUnsigned;
   }
}
