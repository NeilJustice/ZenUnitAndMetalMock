#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<ZenUnitArgs>
   {
   public:
      static void AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs);
   };
}
