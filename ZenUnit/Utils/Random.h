#pragma once
#include "ZenUnit/Enums/PrintMode.h"
#include <random>

namespace ZenUnit
{
   template<typename T>
   T Random();

   template<>
   char Random<char>();

   template<>
   int Random<int>();

   template<>
   unsigned Random<unsigned>();

   template<>
   size_t Random<size_t>();

   template<>
   float Random<float>();

   template<>
   double Random<double>();

   template<>
   std::string Random<std::string>();

   template<>
   PrintMode Random<PrintMode>();
}
