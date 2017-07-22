#pragma once
#include <random>

namespace ZenUnit
{
   template<typename T>
   T TestRandom();

   template<>
   int TestRandom<int>();

   template<>
   unsigned TestRandom<unsigned>();

   template<>
   size_t TestRandom<size_t>();

   template<>
   char TestRandom<char>();

   template<>
   std::string TestRandom<std::string>();
}
