#include "pch.h"
#include "ZenUnit/Console/WindowsColor.h"

namespace ZenUnit
{
   TESTS(WindowsColorTests)
   FACTS(ColorToWindowsColor_ReturnsExpectedWindowsColor)
   AFACT(ColorToWindowsColor_NonWhiteGreenRedColor_TriggersAssertion)
   EVIDENCE

   TEST2X2(ColorToWindowsColor_ReturnsExpectedWindowsColor,
      WindowsColor expectedWindowsColor, Color color,
      WindowsColor::White, Color::White,
      WindowsColor::Green, Color::Green,
      WindowsColor::Teal, Color::Teal,
      WindowsColor::Red, Color::Red)
   {
      const WindowsColor windowsColor = ZenUnit::ColorToWindowsColor(color);
      ARE_EQUAL(expectedWindowsColor, windowsColor);
   }

   TEST(ColorToWindowsColor_NonWhiteGreenRedColor_TriggersAssertion)
   {
      THROWS(ZenUnit::ColorToWindowsColor(Color::Unset),
         logic_error, R"(assert_true(color == Color::Green) failed in ColorToWindowsColor()
File.cpp(1))");
   }

   }; RUNTESTS(WindowsColorTests)
}
