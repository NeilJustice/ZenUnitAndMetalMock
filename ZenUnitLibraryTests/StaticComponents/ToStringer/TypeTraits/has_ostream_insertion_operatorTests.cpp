#include "pch.h"

namespace ZenUnit
{
   TESTS(has_ostream_insertion_operatorTests)
   AFACT(value_IsFalseIfFreeFunctionOStreamInsertionOperatorNotDefinedForType)
   AFACT(value_IsTrueIfFreeFunctionOStreamInsertionOperatorIsDefinedForType)
   EVIDENCE

   TEST(value_IsFalseIfFreeFunctionOStreamInsertionOperatorNotDefinedForType)
   {
      IS_FALSE(has_ostream_insertion_operator<vector<int>>::value);
      IS_FALSE(has_ostream_insertion_operator<NonPrintableUserType>::value);

      IS_FALSE(has_ostream_insertion_operator<UserType>::value);
      IS_FALSE(has_ostream_insertion_operator<UserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<const UserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<UserType&&>::value);

      IS_FALSE(has_ostream_insertion_operator<NonPrintableUserType>::value);
      IS_FALSE(has_ostream_insertion_operator<NonPrintableUserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<const NonPrintableUserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<NonPrintableUserType&&>::value);

      IS_FALSE(has_ostream_insertion_operator<OnlyZenUnitPrintableUserType>::value);
      IS_FALSE(has_ostream_insertion_operator<OnlyZenUnitPrintableUserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<const OnlyZenUnitPrintableUserType&>::value);
      IS_FALSE(has_ostream_insertion_operator<OnlyZenUnitPrintableUserType&&>::value);
   }

   TEST(value_IsTrueIfFreeFunctionOStreamInsertionOperatorIsDefinedForType)
   {
      IS_TRUE(has_ostream_insertion_operator<int>::value);
      IS_TRUE(has_ostream_insertion_operator<int*>::value);

      IS_TRUE(has_ostream_insertion_operator<DoublyPrintableUserType>::value);
      IS_TRUE(has_ostream_insertion_operator<DoublyPrintableUserType&>::value);
      IS_TRUE(has_ostream_insertion_operator<const DoublyPrintableUserType&>::value);
      IS_TRUE(has_ostream_insertion_operator<DoublyPrintableUserType&&>::value);
   }

   RUN_TESTS(has_ostream_insertion_operatorTests)
}
