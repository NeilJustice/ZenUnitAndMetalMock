#pragma once

struct OnlyZenUnitPrintableUserType
{
};

namespace ZenUnit
{
   template<>
   class Printer<OnlyZenUnitPrintableUserType>
   {
   public:
      static void Print(ostream& os, const OnlyZenUnitPrintableUserType&);
   };
}
