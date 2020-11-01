#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<Anomaly>
   {
   public:
      static void AssertEqual(const Anomaly& expectedAnomaly, const Anomaly& actualAnomaly);
   };
}
