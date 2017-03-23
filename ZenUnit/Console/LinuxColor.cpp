#include "pch.h"
#include "LinuxColor.h"
#include "Utils/assert_true.h"

namespace ZenUnit
{
   const char* ColorToLinuxColor(Color color)
   {
      if (color == Color::White)
      {
         return "\033[0m"; // No alteration for white on Linux to prevent white text on a light background
      }
      else if (color == Color::Green)
      {
         return "\033[32m";
      }
      else
      {
         assert_true(color == Color::Red);
         return "\033[31m";      
      }
   }
}
