#pragma once
#include "StaticLibrary/ProgramArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<Args>
   {
      static void AssertEqual(const Args& expectedArgs, const Args& actualArgs);
   };
}
