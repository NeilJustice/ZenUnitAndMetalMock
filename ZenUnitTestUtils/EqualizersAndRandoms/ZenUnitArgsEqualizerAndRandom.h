#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<ZenUnitArgs>
   {
   public:
      static void AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs);
   };

   ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator* randomGenerator);
   template<>
   ZenUnitArgs Random();
}
