#pragma once
#include "ZenUnit/Utils/AssertTrue.h"

struct UserTypeInsOpAndZenUnitPrintable
{
   friend ostream& operator<<(ostream& os, const UserTypeInsOpAndZenUnitPrintable&)
   {
      assert_true(!"operator<< called when ZenUnitPrinter<T>::Print() should have been called");
      return os;
   }
};

template<>
struct ZenUnitPrinter<UserTypeInsOpAndZenUnitPrintable>
{
   static void Print(std::ostream& os, const UserTypeInsOpAndZenUnitPrintable& value);
};
