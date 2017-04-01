#include "pch.h"
#include "LinuxColor.h"
#include "Utils/AssertTrue.h"

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
