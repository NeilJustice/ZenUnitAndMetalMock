#pragma once

struct UserTypeOnlyZenUnitEqualizable
{
   int x = 0;
};

namespace ZenUnit
{
   template<>
   class Equalizer<UserTypeOnlyZenUnitEqualizable>
   {
   public:
      static void AssertEqual(
         const UserTypeOnlyZenUnitEqualizable& expected, const UserTypeOnlyZenUnitEqualizable& actual);
   };
}
