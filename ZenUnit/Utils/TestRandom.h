#pragma once
#include "ZenUnit/Enums/PrintMode.h"
#include <random>

namespace ZenUnit
{
   template<typename T>
   T TestRandom();

   template<>
   PrintMode TestRandom<PrintMode>();

   template<>
   char TestRandom<char>();

   template<>
   int TestRandom<int>();

   template<>
   unsigned TestRandom<unsigned>();

   template<>
   size_t TestRandom<size_t>();

   template<>
   std::string TestRandom<std::string>();
}
