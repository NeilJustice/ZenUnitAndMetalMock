#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<ZenUnitArgs>
   {
      static void AssertEqual(const ZenUnitArgs& expectedArguments, const ZenUnitArgs& actualArgs);
   };
}
