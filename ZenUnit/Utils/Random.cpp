#include "pch.h"
#include "Random.h"

namespace ZenUnit
{
   template<>
   float Random<float>()
   {
      static std::default_random_engine defaultRandomEngine(static_cast<unsigned>(time(nullptr)));
      std::uniform_real_distribution<float> uniformFloatDistribution(-100.0f, 100.0f);
      const float randomFloat = uniformFloatDistribution(defaultRandomEngine);
      return randomFloat;
   }

   template<>
   double Random<double>()
   {
      static std::default_random_engine defaultRandomEngine(static_cast<unsigned>(time(nullptr)));
      std::uniform_real_distribution<double> uniformDoubleDistribution(-100.0, 100.0);
      const double randomDouble = uniformDoubleDistribution(defaultRandomEngine);
      return randomDouble;
   }

   template<>
   std::string Random<std::string>()
   {
      const std::string randomString = "RandomString" + std::to_string(Random<unsigned char>());
      return randomString;
   }
}
