#include "pch.h"

namespace ZenUnit
{
   static_assert(has_ostream_insertion_operator<int>);
   static_assert(has_ostream_insertion_operator<int*>);

   static_assert(has_ostream_insertion_operator<DoublyPrintableUserType>);
   static_assert(has_ostream_insertion_operator<DoublyPrintableUserType&>);
   static_assert(has_ostream_insertion_operator<const DoublyPrintableUserType&>);
   static_assert(has_ostream_insertion_operator<DoublyPrintableUserType&&>);


   static_assert(!has_ostream_insertion_operator<vector<int>>);
   static_assert(!has_ostream_insertion_operator<NonPrintableUserType>);

   static_assert(!has_ostream_insertion_operator<UserType>);
   static_assert(!has_ostream_insertion_operator<UserType&>);
   static_assert(!has_ostream_insertion_operator<const UserType&>);
   static_assert(!has_ostream_insertion_operator<UserType&&>);

   static_assert(!has_ostream_insertion_operator<NonPrintableUserType>);
   static_assert(!has_ostream_insertion_operator<NonPrintableUserType&>);
   static_assert(!has_ostream_insertion_operator<const NonPrintableUserType&>);
   static_assert(!has_ostream_insertion_operator<NonPrintableUserType&&>);

   static_assert(!has_ostream_insertion_operator<OnlyZenUnitPrintableUserType>);
   static_assert(!has_ostream_insertion_operator<OnlyZenUnitPrintableUserType&>);
   static_assert(!has_ostream_insertion_operator<const OnlyZenUnitPrintableUserType&>);
   static_assert(!has_ostream_insertion_operator<OnlyZenUnitPrintableUserType&&>);
}
