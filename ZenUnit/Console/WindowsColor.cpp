#include "pch.h"
#include "WindowsColor.h"
#include "Utils/assert_true.h"

namespace ZenUnit
{
   WindowsColor ColorToWindowsColor(Color color)
   {
      if (color == Color::White)
      {
         return WindowsColor::White;
      }
      else if (color == Color::Green)
      {
         return WindowsColor::Green;
      }      
      else
      {
         assert_true(color == Color::Red);
         return WindowsColor::Red;
      }
   }
}
