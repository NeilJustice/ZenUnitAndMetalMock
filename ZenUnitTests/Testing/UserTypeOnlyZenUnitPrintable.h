#pragma once

struct UserTypeOnlyZenUnitPrintable
{
};

namespace ZenUnit
{
   template<>
   struct Printer<UserTypeOnlyZenUnitPrintable>
   {
      static void Print(ostream& os, const UserTypeOnlyZenUnitPrintable& value);
   };
}
