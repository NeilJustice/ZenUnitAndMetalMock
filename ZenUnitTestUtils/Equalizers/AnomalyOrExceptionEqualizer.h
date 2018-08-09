#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<AnomalyOrException>
   {
      static void AssertEqual(const AnomalyOrException& expectedAnomalyOrException, const AnomalyOrException& actualAnomalyOrException);
   };
}
