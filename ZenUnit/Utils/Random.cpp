#include "pch.h"
#include "Random.h"

namespace ZenUnit
{
   template<>
   float Random<float>()
   {
      return static_cast<float>(Random<double>());
   }

   template<>
   double Random<double>()
   {
      static std::default_random_engine defaultRandomEngine;
      static const std::uniform_real<double> uniformRealDistribution;
      double randomDouble = uniformRealDistribution(defaultRandomEngine);
      return randomDouble;
   }

   template<>
   std::string Random<std::string>()
   {
      return "RandomString" + to_string(Random<unsigned char>());
   }
}
