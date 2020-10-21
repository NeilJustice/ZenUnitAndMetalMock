#pragma once

struct UserTypeInsertionOperatorAndZenUnitPrintable
{
   friend ostream& operator<<(ostream& os, const UserTypeInsertionOperatorAndZenUnitPrintable&)
   {
      assert_true(!"operator<< called when ZenUnit::Printer<T>::Print() should have been called");
      return os;
   }
};

namespace ZenUnit
{
   template<>
   class Printer<UserTypeInsertionOperatorAndZenUnitPrintable>
   {
   public:
      static void Print(ostream& os, const UserTypeInsertionOperatorAndZenUnitPrintable& value);
   };
}
