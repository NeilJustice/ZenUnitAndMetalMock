#include "pch.h"
#include "Random.h"

namespace ZenUnit
{
   template<>
   float Random<float>()
   {
      static std::default_random_engine defaultRandomEngine(static_cast<unsigned>(time(nullptr)));
      static const std::uniform_real<float> uniformRealDistribution(-100.0f, 100.0f);
      float randomFloat = uniformRealDistribution(defaultRandomEngine);
      return randomFloat;
   }

   template<>
   double Random<double>()
   {
      static std::default_random_engine defaultRandomEngine(static_cast<unsigned>(time(nullptr)));
      static const std::uniform_real<double> uniformRealDistribution(-100.0, 100.0);
      double randomDouble = uniformRealDistribution(defaultRandomEngine);
      return randomDouble;
   }

   template<>
   std::string Random<std::string>()
   {
      string randomString = "RandomString" + to_string(Random<unsigned char>());
      return randomString;
   }
}
