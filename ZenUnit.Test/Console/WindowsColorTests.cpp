#include "pch.h"
#include "ZenUnit/Console/WindowsColor.h"

namespace ZenUnit
{
   TESTS(WindowsColorTests)
   SPECX(ColorToWindowsColor_ReturnsExpectedWindowsColor)
   SPEC(ColorToWindowsColor_NonWhiteGreenRedColor_TriggersAssertion)
   SPECEND

   TEST2X2(ColorToWindowsColor_ReturnsExpectedWindowsColor,
      WindowsColor expectedWindowsColor, Color color, 
      WindowsColor::White, Color::White,
      WindowsColor::Green, Color::Green,
      WindowsColor::Red, Color::Red)
   {
      WindowsColor windowsColor = ZenUnit::ColorToWindowsColor(color);
      ARE_EQUAL(expectedWindowsColor, windowsColor);
   }

   TEST(ColorToWindowsColor_NonWhiteGreenRedColor_TriggersAssertion)
   {
      THROWS(ZenUnit::ColorToWindowsColor(Color::Unset),
         logic_error, R"(assert_true(color == Color::Red) failed in ColorToWindowsColor()
File.cpp(1))");
   }

   }; RUN(WindowsColorTests)
}
