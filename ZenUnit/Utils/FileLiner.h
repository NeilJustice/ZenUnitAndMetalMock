#pragma once

namespace ZenUnit
{
   // Header-only-friendly static variable
   template<typename T>
   struct ZenUnitTestingMode
   {
      static T zenUnitTestingMode;
   };

   template<typename T>
   T ZenUnitTestingMode<T>::zenUnitTestingMode;

   struct FileLiner : public ZenUnitTestingMode<bool>
   {
      static const char* File(const char* fileMacroValue);
      static unsigned Line(unsigned lineMacroValue);
   };
}
