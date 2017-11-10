#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Console/ConsoleColorer.h"
#include "ZenUnit/Enums/Color.h"
#include "ZenUnit/Utils/AssertTrue.h"
#ifdef __linux__
#include "ZenUnit/Console/LinuxColor.h"
#include <unistd.h>
#elif _WIN32
#include "ZenUnit/Console/WindowsColor.h"
#include <io.h>
#endif

namespace ZenUnit
{
   INLINE ConsoleColorer::ConsoleColorer()
#ifdef _WIN32
      : call_fileno(::_fileno)
      , call_isatty(::_isatty)
#else
      : call_fileno(::fileno)
      , call_isatty(::isatty)
#endif
#ifdef _WIN32
      , call_GetStdHandle(::GetStdHandle)
      , call_SetConsoleTextAttribute(::SetConsoleTextAttribute)
#endif
      , _supportsColor(false)
      , _supportsColorSet(false)
   {
   }

   INLINE void ConsoleColorer::SetSupportsColorIfUnset()
   {
      if (!_supportsColorSet)
      {
        _supportsColor = SupportsColor();
        _supportsColorSet = true;
      }
   }

   INLINE bool ConsoleColorer::SetColor(Color color)
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

   INLINE void ConsoleColorer::UnsetColor(bool didPreviouslySetTextColor) const
   {
      if (didPreviouslySetTextColor)
      {
         SetTextColor(Color::White);
      }
   }

   INLINE bool ConsoleColorer::SupportsColor() const
   {
      const int stdoutFileHandle = call_fileno(stdout);
      const int isAtty = call_isatty(stdoutFileHandle);
      const bool supportsColor = isAtty != 0;
      return supportsColor;
   }

   INLINE void ConsoleColorer::SetTextColor(Color color) const
   {
#ifdef __linux__
      const char* linuxColor = ColorToLinuxColor(color);
      std::cout << linuxColor;
#elif _WIN32
      const HANDLE stdOutHandle = call_GetStdHandle(STD_OUTPUT_HANDLE);
      const WindowsColor windowsColor = ColorToWindowsColor(color);
      const BOOL didSetConsoleTextAttr = call_SetConsoleTextAttribute(
         stdOutHandle, static_cast<WORD>(windowsColor));
      assert_true(didSetConsoleTextAttr == TRUE);
#endif
   }
}
