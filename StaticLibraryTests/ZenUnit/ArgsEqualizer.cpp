#include "pch.h"
#include "StaticLibrary/Args.h"

namespace ZenUnit
{
   template<>
   void Equalizer<Args>::AssertEqual(const Args& expectedArgs, const Args& actualArgs)
   {
      ARE_EQUAL(expectedArgs.argument1, actualArgs.argument1);
   }
}
