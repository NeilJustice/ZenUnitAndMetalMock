#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<Anomaly>
   {
      static void AssertEqual(const Anomaly& expectedAnomaly, const Anomaly& actualAnomaly);
   };
}
