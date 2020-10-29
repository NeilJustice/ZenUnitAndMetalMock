#include "pch.h"
#include "ZenUnitTestUtils/UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals.h"

namespace ZenUnit
{
   void Equalizer<UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals>::AssertEqual(
      const UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals& expected,
      const UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals& actual)
   {
      ARE_EQUAL(expected.x, actual.x);
   }
}
