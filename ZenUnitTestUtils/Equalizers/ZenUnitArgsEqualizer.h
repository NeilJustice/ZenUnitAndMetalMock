#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<ZenUnitArgs>
   {
   public:
      static void AssertEqual(const ZenUnitArgs& expectedArguments, const ZenUnitArgs& actualArgs);
   };
}
