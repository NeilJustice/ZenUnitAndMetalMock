#include "pch.h"

namespace ZenUnit
{
   TESTS(LinuxColorTests)
   FACTS(ColorToLinuxColor_ReturnsExpected)
   EVIDENCE

   TEST2X2(ColorToLinuxColor_ReturnsExpected,
      Color color, const char* expectedLinuxColor,
      Color::Red, "\033[31m",
      Color::White, "\033[0m",
      Color::Teal, "\033[34m",
      Color::Green, "\033[32m",
      Color::Yellow, "\033[33m",
      Color::Unset, "\033[0m",
      static_cast<Color>(-1), "\033[0m")
   {
      ARE_EQUAL(expectedLinuxColor, ColorToLinuxColor(color));
   }

   RUN_TESTS(LinuxColorTests)
}
