#include "pch.h"
#include "StaticLibrary/ProgramArgs.h"

namespace ZenUnit
{
   template<>
   void Equalizer<ProgramArgs>::AssertEqual(
      const ProgramArgs& expectedProgramArgs,
      const ProgramArgs& actualProgramArgs)
   {
      ARE_EQUAL(expectedProgramArgs.argument1, actualProgramArgs.argument1);
   }
}
