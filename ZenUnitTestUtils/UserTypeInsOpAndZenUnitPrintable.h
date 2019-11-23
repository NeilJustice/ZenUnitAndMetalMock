#pragma once

struct UserTypeInsOpAndZenUnitPrintable
{
   friend ostream& operator<<(ostream& os, const UserTypeInsOpAndZenUnitPrintable&)
   {
      assert_true(!"operator<< called when ZenUnit::Printer<T>::Print() should have been called");
      return os;
   }
};

namespace ZenUnit
{
   template<>
   class Printer<UserTypeInsOpAndZenUnitPrintable>
   {
   public:
      static void Print(ostream& os, const UserTypeInsOpAndZenUnitPrintable& value);
   };
}
