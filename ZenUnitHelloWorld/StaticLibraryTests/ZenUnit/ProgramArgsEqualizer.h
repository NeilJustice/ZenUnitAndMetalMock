#pragma once
#include "StaticLibrary/ProgramArgs.h"

template<>
struct ZenUnitEqualizer
{
   static void AssertEqual(
      const ProgramArgs& expectedProgramArgs, 
      const ProgramArgs& actualProgramArgs);
};
