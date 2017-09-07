#include "pch.h"
#include "StaticLibrary/ProgramArgs.h"

template<>
void ZenUnitEqualizer<ProgramArgs>::AssertEqual(
   const ProgramArgs& expectedProgramArgs,
   const ProgramArgs& actualProgramArgs)
{
   ARE_EQUAL(expectedProgramArgs.flag, actualProgramArgs.flag);
}
