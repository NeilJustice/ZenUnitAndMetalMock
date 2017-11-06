#include "pch.h"
#include "ZenUnit/Console/WindowsColor.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   inline WindowsColor ColorToWindowsColor(Color color)
   {
      switch (color)
      {
      case Color::Red: return WindowsColor::Red;
      case Color::White: return WindowsColor::White;
      case Color::Teal: return WindowsColor::Teal;
      default: assert_true(color == Color::Green); return WindowsColor::Green;
      };
   }
}
