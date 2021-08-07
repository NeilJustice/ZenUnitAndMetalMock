#pragma once

struct OnlyInsertionOperatorPrintableUserType
{
   int x = 0;

   OnlyInsertionOperatorPrintableUserType() = default;
   explicit OnlyInsertionOperatorPrintableUserType(int x);

   friend ostream& operator<<(ostream& os, const OnlyInsertionOperatorPrintableUserType& value)
   {
      os << "OnlyInsertionOperatorPrintableUserType@" << value.x;
      return os;
   }
};
