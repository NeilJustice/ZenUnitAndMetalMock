#pragma once

template<typename T>
struct ZenUnitPrinter;

#include "ZenUnit/ToStringer/ZenUnitPrinter/VectorZenUnitPrinter.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/MapZenUnitPrinter.h"
#include "ZenUnit/ToStringer/ZenUnitPrinter/SetZenUnitPrinter.h"

namespace ZenUnit
{
   template<typename T>
   class has_ZenUnitPrinter
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(::ZenUnitPrinter<U>::Print(os, value));
      template<typename U>
      static std::false_type SFINAE(...);
   public:
      static const bool value = std::is_same<void,
         decltype(SFINAE<T>(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

   template<typename T>
   const bool has_ZenUnitPrinter<T>::value;
}
