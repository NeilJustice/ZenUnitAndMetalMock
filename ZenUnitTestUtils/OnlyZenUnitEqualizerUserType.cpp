#include "pch.h"
#include "ZenUnitTestUtils/OnlyZenUnitEqualizerUserType.h"

namespace ZenUnit
{
   void Equalizer<OnlyZenUnitEqualizerUserType>::AssertEqual(const OnlyZenUnitEqualizerUserType& expected, const OnlyZenUnitEqualizerUserType& actual)
   {
      ARE_EQUAL(expected.x, actual.x);
   }

   void Printer<OnlyZenUnitEqualizerUserType>::Print(ostream& os, const OnlyZenUnitEqualizerUserType& onlyZenUnitEqualizerUserType)
   {
      os << "OnlyZenUnitEqualizerUserType@" << onlyZenUnitEqualizerUserType.x;
   }
}
