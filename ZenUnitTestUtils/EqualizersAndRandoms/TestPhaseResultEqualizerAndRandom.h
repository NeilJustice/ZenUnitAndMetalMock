#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestPhaseResult>
   {
   public:
      static void AssertEqual(const TestPhaseResult& expectedTestPhaseResult, const TestPhaseResult& actualTestPhaseResult);
   };

   template<>
   TestPhaseResult Random<TestPhaseResult>();
   TestPhaseResult TestableRandomTestPhaseResult(const RandomGenerator& randomGenerator);
}
