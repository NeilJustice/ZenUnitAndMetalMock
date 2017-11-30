#include "pch.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#include "ZenUnit/Console/WindowsColor.h"
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <io.h>
// fileno() and isatty() are Linux and Windows wheras _fileno() and _isatty() are Windows only
#pragma warning(disable: 4996) // 'fileno': The POSIX name for this item is deprecated
#endif

namespace ZenUnit
{
   TESTS(ConsoleColorerTests)
   AFACT(Constructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   FACTS(SetSupportsColorIfUnset_SetsSupportsColorIfUnset)
   FACTS(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite)
   FACTS(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue)
   FACTS(SupportsColor_ReturnsTrueIfStdoutIsATTY)
#ifdef _WIN32
   FACTS(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor)
#endif
   EVIDENCE

   struct ConsoleColorer_SupportsColorMocked : public Zen::Mock<ConsoleColorer>
   {
      ZENMOCK_NONVOID0_CONST(bool, SupportsColor)
   };

   struct ConsoleColorer_SetCallsMocked : public Zen::Mock<ConsoleColorer>
   {
      ZENMOCK_VOID0(SetSupportsColorIfUnset)
      ZENMOCK_VOID1_CONST(SetTextColor, Color)
   };

   ConsoleColorer _consoleColorer;
   ConsoleColorer_SupportsColorMocked _consoleColorer_SupportsColorMocked;
   ConsoleColorer_SetCallsMocked _consoleColorer_SetCallsMocked;

   TEST(Constructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   {
      const ConsoleColorer consoleColorer;
      STD_FUNCTION_TARGETS(::fileno, consoleColorer.call_fileno);
      STD_FUNCTION_TARGETS(::isatty, consoleColorer.call_isatty);
#ifdef _WIN32
      STD_FUNCTION_TARGETS(::GetStdHandle, consoleColorer.call_GetStdHandle);
      STD_FUNCTION_TARGETS(::SetConsoleTextAttribute, consoleColorer.call_SetConsoleTextAttribute);
#endif
      IS_FALSE(consoleColorer._supportsColor);
      IS_FALSE(consoleColorer._supportsColorSet);
   }

   TEST2X2(SetSupportsColorIfUnset_SetsSupportsColorIfUnset,
      bool supportsColorSet, bool expectSupportsColorCall,
      false, true,
      true, false)
   {
      _consoleColorer_SupportsColorMocked._supportsColorSet = supportsColorSet;
      const bool supportsColorReturnValue = ZenUnit::Random<bool>();
      if (expectSupportsColorCall)
      {
         _consoleColorer_SupportsColorMocked.SupportsColorMock.ExpectAndReturn(supportsColorReturnValue);
      }
      //
      _consoleColorer_SupportsColorMocked.SetSupportsColorIfUnset();
      //
      if (expectSupportsColorCall)
      {
         ZEN(_consoleColorer_SupportsColorMocked.SupportsColorMock.AssertCalledOnce());
         ARE_EQUAL(_consoleColorer_SupportsColorMocked._supportsColor, supportsColorReturnValue);
      }
      IS_TRUE(_consoleColorer_SupportsColorMocked._supportsColorSet);
   }

   TEST3X3(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite,
      Color color,
      bool supportsColor,
      bool expectSetTextColorCallAndExpectedReturnValue,
      Color::White, false, false,
      Color::White, true, false,
      Color::Green, false, false,
      Color::Green, true, true,
      Color::Red, false, false,
      Color::Red, true, true,
      Color::Red, false, false,
      Color::Teal, true, true)
   {
      _consoleColorer_SetCallsMocked._supportsColor = supportsColor;
      _consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.Expect();
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.Expect();
      }
      //
      bool didSetColor = _consoleColorer_SetCallsMocked.SetColor(color);
      //
      ZEN(_consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.AssertCalledOnce());
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         ZEN(_consoleColorer_SetCallsMocked.SetTextColorMock.AssertCalledOnceWith(color));
      }
      ARE_EQUAL(expectSetTextColorCallAndExpectedReturnValue, didSetColor);
   }

   TEST2X2(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue,
      bool didSetTextColor, bool expectSetTextColorWhite,
      false, false,
      true, true)
   {
      if (expectSetTextColorWhite)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.Expect();
      }
      //
      _consoleColorer_SetCallsMocked.UnsetColor(didSetTextColor);
      //
      if (expectSetTextColorWhite)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.AssertCalledOnceWith(Color::White);
      }
   }

   TEST2X2(SupportsColor_ReturnsTrueIfStdoutIsATTY,
      int isattyReturnValue, bool expectedReturnValue,
      -1, true,
      0, false,
      1, true)
   {
      ZENMOCK_NONVOID1_FREE(int, fileno, FILE*);
      ZENMOCK_NONVOID1_FREE(int, isatty, int);
      const int StdoutFileHandle = 1;
      fileno_ZenMock.ExpectAndReturn(StdoutFileHandle);
      isatty_ZenMock.ExpectAndReturn(isattyReturnValue);
      _consoleColorer.call_fileno = ZENMOCK_BIND1(fileno_ZenMock);
      _consoleColorer.call_isatty = ZENMOCK_BIND1(isatty_ZenMock);
      //
      const bool consoleSupportsColor = _consoleColorer.SupportsColor();
      //
      ZEN(fileno_ZenMock.AssertCalledOnceWith(stdout));
      ZEN(isatty_ZenMock.AssertCalledOnceWith(StdoutFileHandle));
      ARE_EQUAL(expectedReturnValue, consoleSupportsColor);
   }

#ifdef _WIN32
   TEST2X2(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor,
      Color color, WindowsColor expectedWindowsColor,
      Color::White, WindowsColor::White,
      Color::Green, WindowsColor::Green,
      Color::Red, WindowsColor::Red,
      Color::Teal, WindowsColor::Teal)
   {
      ZENMOCK_NONVOID1_FREE(HANDLE, GetStdHandle, DWORD);
      ZENMOCK_NONVOID2_FREE(BOOL, SetConsoleTextAttribute, HANDLE, WORD);
      _consoleColorer.call_GetStdHandle = ZENMOCK_BIND1(GetStdHandle_ZenMock);
      _consoleColorer.call_SetConsoleTextAttribute = ZENMOCK_BIND2(SetConsoleTextAttribute_ZenMock);

      const HANDLE GetStdHandleReturnValue = HANDLE(1);
      GetStdHandle_ZenMock.ExpectAndReturn(GetStdHandleReturnValue);

      SetConsoleTextAttribute_ZenMock.ExpectAndReturn(TRUE);
      //
      _consoleColorer.SetTextColor(color);
      //
      GetStdHandle_ZenMock.AssertCalledOnceWith(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute_ZenMock.AssertCalledOnceWith(
         GetStdHandleReturnValue, static_cast<WORD>(expectedWindowsColor));
   }
#endif

   }; RUNTESTS(ConsoleColorerTests)
}
