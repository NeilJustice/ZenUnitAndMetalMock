#pragma once

struct OnlyZenUnitEqualizerUserType
{
   int x = 0;
};

namespace ZenUnit
{
   template<>
   class Equalizer<OnlyZenUnitEqualizerUserType>
   {
   public:
      static void AssertEqual(const OnlyZenUnitEqualizerUserType& expected, const OnlyZenUnitEqualizerUserType& actual);
   };

   template<>
   class Printer<OnlyZenUnitEqualizerUserType>
   {
   public:
      static void Print(ostream& os, const OnlyZenUnitEqualizerUserType&);
   };
}
