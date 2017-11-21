#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

namespace ZenUnit
{
   template<typename T>
   struct Equalizer<std::vector<T>>
   {
      static void AssertEqual(const std::vector<T>& expectedVector, const std::vector<T>& actualVector)
      {
         VECTORS_EQUAL(expectedVector, actualVector);
      }
   };
}
