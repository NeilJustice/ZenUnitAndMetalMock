#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<TestPhaseResult>
   {
      static void AssertEqual(const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult);
   };
}
