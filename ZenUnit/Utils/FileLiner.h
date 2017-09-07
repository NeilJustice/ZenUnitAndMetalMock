#pragma once

namespace ZenUnit
{
   struct FileLiner
   {
      static bool selfTestMode;
      static const char* File(const char* fileMacroValue);
      static unsigned Line(unsigned lineMacroValue);
   };
}
