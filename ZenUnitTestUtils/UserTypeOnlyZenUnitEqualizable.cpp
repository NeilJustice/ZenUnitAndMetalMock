#include "pch.h"
#include "ZenUnitTestUtils/UserTypeOnlyZenUnitEqualizable.h"

namespace ZenUnit
{
   void Equalizer<UserTypeOnlyZenUnitEqualizable>::AssertEqual(
      const UserTypeOnlyZenUnitEqualizable& expected, const UserTypeOnlyZenUnitEqualizable& actual)
   {
      ARE_EQUAL(expected.x, actual.x);
   }
}
