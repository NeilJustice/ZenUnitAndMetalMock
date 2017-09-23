#pragma once

namespace ZenUnit
{
   template<typename T>
   struct SingleHeaderStaticVariable
   {
      static T single_header_static;
   };

   template<typename T>
   T SingleHeaderStaticVariable<T>::single_header_static;
}
