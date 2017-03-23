#include "pch.h"
#include "UserType.h"

TESTS(UserTypeTests)
SPEC(DefaultConstructor_SetsValueTo0)
SPEC(OneArgConstructor_SetsValue)
SPEC(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
SPEC(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
SPEC(ZenUnitPrint_WritesExpected_ReturnOStream)
SPEC(OperatorBool_ValueIs1_ReturnsTrue)
SPEC(OperatorBool_ValueIsNot1_ReturnsFalse)
SPEC(has_ostream_left_shift_False)
SPEC(has_ZenUnitPrinter_True)
SPECEND

TEST(DefaultConstructor_SetsValueTo0)
{
   UserType userType;
   IS_ZERO(userType.value);
}

TEST(OneArgConstructor_SetsValue)
{
   UserType userType(1);
   ARE_EQUAL(1, userType.value);
}

TEST(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
{
   UserType userType1(1);
   UserType userType2(2);
   IS_TRUE(userType1 < userType2);
   IS_FALSE(userType2 < userType1);
   IS_FALSE(userType1 < userType1);
}

TEST(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
{
   UserType userType1(1);
   UserType userType2(2);
   IS_TRUE(userType1 == userType1);
   IS_FALSE(userType1 == userType2);
}

TEST(ZenUnitPrint_WritesExpected_ReturnOStream)
{
   UserType userType1(1);
   UserType userTypeNegative1(-1);
   ostringstream oss;
   //
   ZenUnitPrinter<UserType>::Print(oss, userType1);
   oss << " ";
   ZenUnitPrinter<UserType>::Print(oss, userTypeNegative1);
   //
   ARE_EQUAL("UserType@1 UserType@-1", oss.str());
}

TEST(OperatorBool_ValueIs1_ReturnsTrue)
{
   UserType userType1(1);
   IS_TRUE(userType1);
   IS_TRUE(userType1);
}

TEST(OperatorBool_ValueIsNot1_ReturnsFalse)
{
   UserType userTypeNegative1(-1);
   IS_FALSE(userTypeNegative1);
   IS_FALSE(userTypeNegative1);

   UserType userType0(0);
   IS_FALSE(userType0);
   IS_FALSE(userType0);

   UserType userType2(2);
   IS_FALSE(userType2);
   IS_FALSE(userType2);
}

TEST(has_ostream_left_shift_False)
{
   IS_FALSE(ZenUnit::has_ostream_left_shift<UserType>::value);
}

TEST(has_ZenUnitPrinter_True)
{
   IS_TRUE(ZenUnit::has_ZenUnitPrinter<UserType>::value);
}

}; RUN(UserTypeTests)
