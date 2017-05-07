#include "pch.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Enums/WindowsColor.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   WindowsColor ColorToWindowsColor(Color color)
   {
      switch (color)
      {
      case Color::White: return WindowsColor::White;
      case Color::Green: return WindowsColor::Green;
      default: assert_true(color == Color::Red); return WindowsColor::Red;
      };
   }
}
