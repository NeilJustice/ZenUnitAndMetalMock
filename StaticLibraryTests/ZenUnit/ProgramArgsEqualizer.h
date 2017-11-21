#pragma once
#include "StaticLibrary/ProgramArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<ProgramArgs>
   {
      static void AssertEqual(
         const ProgramArgs& expectedProgramArgs,
         const ProgramArgs& actualProgramArgs);
   };
}
