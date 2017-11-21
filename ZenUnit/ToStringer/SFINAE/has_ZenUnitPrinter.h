#pragma once

namespace ZenUnit
{
   template<typename T>
   struct Printer;
}

#include "ZenUnit/ToStringer/ZenUnitPrinter/MapZenUnitPrinter.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/SetZenUnitPrinter.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/VectorZenUnitPrinter.h"

namespace ZenUnit
{
   template<typename T>
   class has_ZenUnitPrinter
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(ZenUnit::Printer<U>::Print(os, value));
      template<typename U>
      static std::false_type SFINAE(...);
   public:
      static const bool value = std::is_same<void,
         decltype(SFINAE<T>(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

   template<typename T>
   const bool has_ZenUnitPrinter<T>::value;
}
