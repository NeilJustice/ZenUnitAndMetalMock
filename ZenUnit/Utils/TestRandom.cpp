#include "pch.h"
#include "TestRandom.h"

namespace ZenUnit
{
   template<>
   int TestRandom<int>()
   {
      static std::default_random_engine defaultRandomEngine;
      defaultRandomEngine.seed(static_cast<unsigned int>(time(NULL)));
      static const std::uniform_int_distribution<int> distribution(-100, 101);
      const int randomValue = distribution(defaultRandomEngine);
      return randomValue;
   }

   template<>
   unsigned TestRandom<unsigned>()
   {
      return static_cast<unsigned>(TestRandom<int>());
   }

   template<>
   size_t TestRandom<size_t>()
   {
      return static_cast<size_t>(TestRandom<int>());
   }

   template<>
   char TestRandom<char>()
   {
      return static_cast<char>(TestRandom<int>());
   }

   template<>
   std::string TestRandom<std::string>()
   {
      return "RandomString" + to_string(TestRandom<int>());
   }
}
