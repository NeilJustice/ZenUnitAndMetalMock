#pragma once
#include <chrono>

namespace ZenUnit
{
   class Stopwatch
   {
      friend class StopwatchTests;
   private:
      std::function<std::chrono::time_point<
         std::chrono::high_resolution_clock>()> _highres_now_ZenMockable;
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch();
      virtual ~Stopwatch() = default;
      virtual void Start();
      virtual unsigned Stop();
   };
}
