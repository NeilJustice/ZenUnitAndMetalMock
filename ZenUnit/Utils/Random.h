#pragma once
#include "ZenUnit/Enums/PrintMode.h"
#include <random>

namespace ZenUnit
{
   template<typename T>
   T Random(long long inclusiveLowerBound, unsigned long long inclusiveUpperBound)
   {
      static std::default_random_engine defaultRandomEngine(static_cast<unsigned>(time(nullptr)));
      const long long adjustedInclusiveLowerBound = inclusiveLowerBound < 0 ? 0 : inclusiveLowerBound;
      const unsigned long long adjustedInclusiveUpperBound =
         inclusiveLowerBound < 0 ? 2 * inclusiveUpperBound + 1 : inclusiveUpperBound;
      std::uniform_int_distribution<unsigned long long>
         distribution(adjustedInclusiveLowerBound, adjustedInclusiveUpperBound);
      const unsigned long long randomValueUnsignedLongLong = distribution(defaultRandomEngine);
      const T randomValueT = static_cast<T>(randomValueUnsignedLongLong);
      return randomValueT;
   }

   template<typename T>
   T Random()
   {
      return Random<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
   }

   template<>
   float Random<float>();

   template<>
   double Random<double>();

   template<>
   std::string Random<std::string>();
}
