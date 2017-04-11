#include "pch.h"
#include "UserTypeNonPrintable.h"
#include "ZenUnit/ToStringer/SFINAE/has_ostream_left_shift.h"

namespace ZenUnit
{
   TESTS(UserTypeNonPrintableTests)
   SPEC(DefaultConstructor_SetsXTo0)
   SPEC(OneArgConstructor_SetsX)
   SPEC(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
   SPEC(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
   SPEC(has_ostream_left_shift_ValueEqualsFalse)
   SPECEND

   TEST(DefaultConstructor_SetsXTo0)
   {
      const UserTypeNonPrintable userType;
      IS_ZERO(userType.x);
   }

   TEST(OneArgConstructor_SetsX)
   {
      const UserTypeNonPrintable userType(1);
      ARE_EQUAL(1, userType.x);
   }

   TEST(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
   {
      const UserTypeNonPrintable userType1(1);
      const UserTypeNonPrintable userType2(2);
      IS_TRUE(userType1 < userType2);
      IS_FALSE(userType2 < userType1);
      IS_FALSE(userType1 < userType1);
   }

   TEST(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
   {
      const UserTypeNonPrintable userType1(1);
      const UserTypeNonPrintable userType2(2);
      IS_TRUE(userType1 == userType1);
      IS_FALSE(userType1 == userType2);
   }

   TEST(has_ostream_left_shift_ValueEqualsFalse)
   {
      IS_FALSE(has_ostream_left_shift<UserTypeNonPrintable>::value);
   }

   }; RUN(UserTypeNonPrintableTests)
}
