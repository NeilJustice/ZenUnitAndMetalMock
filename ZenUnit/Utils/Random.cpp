#include "pch.h"
#include "Random.h"

namespace ZenUnit
{
   template<>
   PrintMode Random<PrintMode>()
   {
      static std::default_random_engine defaultRandomEngine;
      defaultRandomEngine.seed(static_cast<unsigned int>(time(NULL)));
      static const std::uniform_int_distribution<int> distribution(0, 3);
      const int randomInt = distribution(defaultRandomEngine);
      PrintMode randomPrintMode = static_cast<PrintMode>(randomInt);
      return randomPrintMode;
   }

   template<>
   char Random<char>()
   {
      return static_cast<char>(Random<int>());
   }

   template<>
   int Random<int>()
   {
      static std::default_random_engine defaultRandomEngine;
      defaultRandomEngine.seed(static_cast<unsigned int>(time(NULL)));
      static const std::uniform_int_distribution<int> distribution(-100, 101);
      const int randomInt = distribution(defaultRandomEngine);
      return randomInt;
   }

   template<>
   unsigned Random<unsigned>()
   {
      return static_cast<unsigned>(Random<int>());
   }

   template<>
   size_t Random<size_t>()
   {
      return static_cast<size_t>(Random<int>());
   }

   template<>
   std::string Random<std::string>()
   {
      return "RandomString" + to_string(Random<int>());
   }
}
