#pragma once

namespace ZenUnit
{
   enum class Color : unsigned char;

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
