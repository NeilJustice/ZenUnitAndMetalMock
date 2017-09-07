#pragma once
#include "StaticLibrary/ProgramArgs.h"

template<>
struct ZenUnitEqualizer<ProgramArgs>
{
   static void AssertEqual(
      const ProgramArgs& expectedProgramArgs,
      const ProgramArgs& actualProgramArgs);
};
