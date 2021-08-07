#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<AnomalyOrException>
   {
   public:
      static void AssertEqual(
         const AnomalyOrException& expectedAnomalyOrException, const AnomalyOrException& actualAnomalyOrException);
   };

   AnomalyOrException TestableRandomAnomalyOrException(const RandomGenerator* randomGenerator);
   template<>
   AnomalyOrException Random();
}
