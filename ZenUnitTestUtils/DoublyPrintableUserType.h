#pragma once

struct DoublyPrintableUserType
{
   friend ostream& operator<<(ostream& os, const DoublyPrintableUserType&)
   {
      assert_true(!"operator<< called when ZenUnit::Printer<T>::Print() should have been called");
      return os;
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
