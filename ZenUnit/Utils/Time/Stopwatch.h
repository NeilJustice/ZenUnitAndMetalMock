#pragma once
#include <chrono>

namespace ZenUnit
{
   class Stopwatch
   {
      friend class StopwatchTests;
   private:
      std::function<std::chrono::time_point<
         std::chrono::high_resolution_clock>()> call_highres_now;
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch();
      virtual ~Stopwatch() = default;
      virtual void Start();
      virtual unsigned Stop();
   };
}
