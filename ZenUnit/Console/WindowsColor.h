#pragma once
#include "ZenUnit/Console/Color.h"

namespace ZenUnit
{
   enum class WindowsColor : unsigned char
   {
      Black,
      DarkBlue,
      DarkGreen,
      DarkTeal,
      DarkRed,
      DarkPink,
      DarkYellow,
      Gray,
      DarkGray,
      Blue,
      Green,
      Teal,
      Red,
      Pink,
      Yellow,
      White
   };

   WindowsColor ColorToWindowsColor(Color color);
}
