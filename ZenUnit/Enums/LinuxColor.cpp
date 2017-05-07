#include "pch.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Enums/LinuxColor.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   const char* ColorToLinuxColor(Color color)
   {
      switch (color)
      {
      case Color::White: return "\033[0m";
      case Color::Green: return "\033[32m";
      default: assert_true(color == Color::Red); return "\033[31m";
      };
   }
}
