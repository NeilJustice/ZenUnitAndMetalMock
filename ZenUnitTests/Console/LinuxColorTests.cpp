#include "pch.h"
#include "ZenUnit/Console/LinuxColor.h"

namespace ZenUnit
{
   TESTS(LinuxColorTests)
   FACTS(ColorToLinuxColor_ReturnsExpected)
   AFACT(ColorToLinuxColor_NonWhiteGreenRedColor_TriggersAssertion)
   EVIDENCE

   TEST2X2(ColorToLinuxColor_ReturnsExpected,
      const char* expectedColorCode, Color color,
      "\033[31m", Color::Red,
      "\033[0m", Color::White,
      "\033[34m", Color::Teal,
      "\033[32m", Color::Green)
   {
      ARE_EQUAL(expectedColorCode, ColorToLinuxColor(color));
   }

   TEST(ColorToLinuxColor_NonWhiteGreenRedColor_TriggersAssertion)
   {
      THROWS(ZenUnit::ColorToLinuxColor(Color::Unset),
         logic_error, R"(assert_true(color == Color::Green) failed in ColorToLinuxColor()
File.cpp(1))");
   }

   }; RUNTESTS(LinuxColorTests)
}
