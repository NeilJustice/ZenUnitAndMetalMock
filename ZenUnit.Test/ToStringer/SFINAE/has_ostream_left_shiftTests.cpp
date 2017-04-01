#include "pch.h"
#include "ZenUnit.Test/Testing/UserTypeInsOpAndZenUnitPrintable.h"
#include "ZenUnit.Test/Testing/UserTypeOnlyZenUnitPrintable.h"
#include "ZenUnit/ToStringer/SFINAE/has_ostream_left_shift.h"

namespace ZenUnit
{
   TESTS(has_ostream_left_shiftTests)
   SPEC(value_IsFalseIfGlobalOStreamInsertionOperatorNotDefinedForType)
   SPEC(value_IsTrueIfGlobalOStreamInsertionOperatorIsDefinedForType)
   SPECEND

   TEST(value_IsFalseIfGlobalOStreamInsertionOperatorNotDefinedForType)
   {
      IS_FALSE(has_ostream_left_shift<vector<int>>::value);
      IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable>::value);

      IS_FALSE(has_ostream_left_shift<UserType>::value);
      IS_FALSE(has_ostream_left_shift<UserType&>::value);
      IS_FALSE(has_ostream_left_shift<const UserType&>::value);
      IS_FALSE(has_ostream_left_shift<UserType&&>::value);

      IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable>::value);
      IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable&>::value);
      IS_FALSE(has_ostream_left_shift<const UserTypeNonPrintable&>::value);
      IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable&&>::value);

      IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable>::value);
      IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable&>::value);
      IS_FALSE(has_ostream_left_shift<const UserTypeOnlyZenUnitPrintable&>::value);
      IS_FALSE(has_ostream_left_shift<UserTypeOnlyZenUnitPrintable&&>::value);
   }

   TEST(value_IsTrueIfGlobalOStreamInsertionOperatorIsDefinedForType)
   {
      IS_TRUE(has_ostream_left_shift<int>::value);
      IS_TRUE(has_ostream_left_shift<int*>::value);

      IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable>::value);
      IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable&>::value);
      IS_TRUE(has_ostream_left_shift<const UserTypeInsOpAndZenUnitPrintable&>::value);
      IS_TRUE(has_ostream_left_shift<UserTypeInsOpAndZenUnitPrintable&&>::value);
   }

   }; RUN(has_ostream_left_shiftTests)
}
