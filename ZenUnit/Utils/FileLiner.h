#pragma once

namespace ZenUnit
{
   template<typename T>
   struct ZenUnitTestingMode
   {
      static bool zenUnitTestingMode;
   };

   // Header-only-friendly static variable
   template<> bool ZenUnitTestingMode<bool>::zenUnitTestingMode;

   struct FileLiner : public ZenUnitTestingMode<bool>
   {
      static const char* File(const char* fileMacroValue);
      static unsigned Line(unsigned lineMacroValue);
   };
}
