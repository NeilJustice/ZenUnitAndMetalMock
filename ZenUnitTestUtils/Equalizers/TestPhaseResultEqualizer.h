#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestPhaseResult>
   {
   public:
      static void AssertEqual(const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult);
   };
}
