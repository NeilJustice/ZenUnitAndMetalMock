#include "pch.h"

namespace ZenUnit
{
   TESTS(LinuxColorTests)
   FACTS(ColorToLinuxColor_ReturnsExpected)
   EVIDENCE

   TEST2X2(ColorToLinuxColor_ReturnsExpected,
      const char* expectedColorCode, Color color,
      "\033[31m", Color::Red,
      "\033[0m", Color::White,
      "\033[34m", Color::Teal,
      "\033[32m", Color::Green,
      "\033[0m", Color::Unset,
      "\033[0m", static_cast<Color>(-1))
   {
      ARE_EQUAL(expectedColorCode, ColorToLinuxColor(color));
   }

   }; RUNTESTS(LinuxColorTests)
}
