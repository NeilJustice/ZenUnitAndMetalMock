#pragma once
#include "ZenUnit/Enums/PrintMode.h"
#include <random>

namespace ZenUnit
{
   template<typename T>
   T Random();

   template<>
   PrintMode Random<PrintMode>();

   template<>
   char Random<char>();

   template<>
   int Random<int>();

   template<>
   unsigned Random<unsigned>();

   template<>
   size_t Random<size_t>();

   template<>
   std::string Random<std::string>();
}
