#include "pch.h"

#if defined _WIN32
namespace ZenUnit
{
   TESTS(WindowsColorTests)
   FACTS(ColorToWindowsColor_ReturnsExpectedWindowsColor)
   EVIDENCE

   TEST2X2(ColorToWindowsColor_ReturnsExpectedWindowsColor,
      Color color, WindowsColor expectedWindowsColor,
      Color::Red, WindowsColor::Red,
      Color::White, WindowsColor::White,
      Color::Teal, WindowsColor::Teal,
      Color::Green, WindowsColor::Green,
      Color::Yellow, WindowsColor::Yellow,
      Color::Unset, WindowsColor::White,
      static_cast<Color>(-1), WindowsColor::White)
   {
      const WindowsColor windowsColor = ZenUnit::ColorToWindowsColor(color);
      ARE_EQUAL(expectedWindowsColor, windowsColor);
   }

   RUN_TESTS(WindowsColorTests)
}
#endif
