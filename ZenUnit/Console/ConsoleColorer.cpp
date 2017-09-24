#include "pch.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Utils/AssertTrue.h"
#ifdef __linux__
#include "ZenUnit/Enums/LinuxColor.h"
#include <unistd.h>
#elif _WIN32
#include "ZenUnit/Enums/WindowsColor.h"
#include <io.h>
#endif

namespace ZenUnit
{
   ConsoleColorer::ConsoleColorer()
#ifdef _WIN32
      : fileno_ZenMockable(::_fileno)
      , isatty_ZenMockable(::_isatty)
#else
      : fileno_ZenMockable(::fileno)
      , isatty_ZenMockable(::isatty)
#endif
#ifdef _WIN32
      , GetStdHandle_ZenMockable(::GetStdHandle)
      , SetConsoleTextAttribute_ZenMockable(::SetConsoleTextAttribute)
#endif
      , _supportsColor(false)
      , _supportsColorSet(false)
   {
   }

   void ConsoleColorer::SetSupportsColorIfUnset()
   {
      if (!_supportsColorSet)
      {
        _supportsColor = SupportsColor();
        _supportsColorSet = true;
      }
   }

   bool ConsoleColorer::SetColor(Color color)
   {
      SetSupportsColorIfUnset();
      const bool doSetTextColor = color != Color::White && _supportsColor;
      if (doSetTextColor)
      {
         SetTextColor(color);
         return true;
      }
      return false;
   }

   void ConsoleColorer::UnsetColor(bool didPreviouslySetTextColor) const
   {
      if (didPreviouslySetTextColor)
      {
         SetTextColor(Color::White);
      }
   }

   bool ConsoleColorer::SupportsColor() const
   {
      const int stdoutFileHandle = fileno_ZenMockable(stdout);
      const int isAtty = isatty_ZenMockable(stdoutFileHandle);
      const bool supportsColor = isAtty != 0;
      return supportsColor;
   }

   void ConsoleColorer::SetTextColor(Color color) const
   {
#ifdef __linux__
      const char* linuxColor = ColorToLinuxColor(color);
      std::cout << linuxColor;
#elif _WIN32
      const HANDLE stdOutHandle = GetStdHandle_ZenMockable(STD_OUTPUT_HANDLE);
      const WindowsColor windowsColor = ColorToWindowsColor(color);
      const BOOL didSetConsoleTextAttr = SetConsoleTextAttribute_ZenMockable(
         stdOutHandle, static_cast<WORD>(windowsColor));
      assert_true(didSetConsoleTextAttr == TRUE);
#endif
   }
}
