#pragma once

struct DoublyPrintableUserType
{
   [[noreturn]] friend ostream& operator<<(ostream&, const DoublyPrintableUserType&)
   {
      throw logic_error("operator<< called when ZenUnit::Printer<T>::Print() should have been called");
   }
};

namespace ZenUnit
{
   template<>
   class Printer<DoublyPrintableUserType>
   {
   public:
      static void Print(ostream& os, const DoublyPrintableUserType& value);
   };
}
