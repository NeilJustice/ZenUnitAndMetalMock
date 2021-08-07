#pragma once
class ZenUnitTestingRandomGenerator;

namespace ZenUnit
{
   template<>
   class Equalizer<ZenUnitArgs>
   {
   public:
      static void AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs);
   };

   ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator* randomGenerator, const ZenUnitTestingRandomGenerator* zenUnitTestingRandomGenerator);
   template<>
   ZenUnitArgs Random();
}
