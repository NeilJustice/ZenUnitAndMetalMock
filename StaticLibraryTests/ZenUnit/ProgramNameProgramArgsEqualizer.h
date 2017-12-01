#pragma once
#include "StaticLibrary/ProgramArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<ProgramNameArgs>
   {
      static void AssertEqual(
         const ProgramNameArgs& expectedProgramArgs,
         const ProgramNameArgs& actualProgramArgs);
   };
}
