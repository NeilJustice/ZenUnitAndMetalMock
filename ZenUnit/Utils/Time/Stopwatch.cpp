#include "pch.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   Stopwatch::Stopwatch()
      : call_highres_now(std::chrono::high_resolution_clock::now)
   {
   }

   void Stopwatch::Start()
   {
      _startTime = call_highres_now();
   }

   unsigned Stopwatch::Stop()
   {
      if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
      {
         return 0;
      }
      const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = call_highres_now();
      const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
      const long long elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();
      _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
      assert_true(elapsedMilliseconds <= std::numeric_limits<unsigned>::max());
      const unsigned elapsedMillisecondsUnsigned = static_cast<unsigned>(elapsedMilliseconds);
      return elapsedMillisecondsUnsigned;
   }
}
