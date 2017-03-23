#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

template<typename T>
struct ZenUnitEqualizer<std::vector<T>>
{
   static void AssertEqual(const std::vector<T>& expectedVector, const std::vector<T>& actualVector)
   {
      VECTORS_EQUAL(expectedVector, actualVector);
   }
};
