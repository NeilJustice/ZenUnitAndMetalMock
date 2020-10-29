#pragma once

struct UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals
{
   int x = 0;
};

namespace ZenUnit
{
   template<>
   class Equalizer<UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals>
   {
   public:
      static void AssertEqual(
         const UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals& expected,
         const UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals& actual);
   };
}
