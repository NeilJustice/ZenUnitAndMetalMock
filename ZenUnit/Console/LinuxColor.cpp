#include "pch.h"
#include "ZenUnit/Console/LinuxColor.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   const char* ColorToLinuxColor(Color color)
   {
      switch (color)
      {
      case Color::Red: return "\033[31m";
      case Color::White: return "\033[0m";
      case Color::Teal: return "\033[34m";
      default: assert_true(color == Color::Green); return "\033[32m";
      };
   }
}
