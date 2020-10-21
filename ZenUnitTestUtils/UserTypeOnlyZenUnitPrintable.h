#pragma once

struct UserTypeOnlyZenUnitPrintable
{
};

namespace ZenUnit
{
   template<>
   class Printer<UserTypeOnlyZenUnitPrintable>
   {
   public:
      static void Print(ostream& os, const UserTypeOnlyZenUnitPrintable&);
   };
}
