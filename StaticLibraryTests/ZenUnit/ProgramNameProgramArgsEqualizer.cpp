#include "pch.h"
#include "StaticLibrary/ProgramNameArgs.h"

namespace ZenUnit
{
   template<>
   void Equalizer<ProgramNameArgs>::AssertEqual(
      const ProgramNameArgs& expectedProgramArgs,
      const ProgramNameArgs& actualProgramArgs)
   {
      ARE_EQUAL(expectedProgramArgs.argument1, actualProgramArgs.argument1);
   }
}
