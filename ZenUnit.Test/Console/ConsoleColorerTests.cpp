#include "pch.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <io.h>
#include "ZenUnit/Console/WindowsColor.h"
// fileno() and isatty() are Linux and Windows wheras _fileno() and _isatty() are Windows only
#pragma warning(disable: 4996) // 'fileno': The POSIX name for this item is deprecated
#endif

struct ConsoleColorerSelfMocked : public Zen::Mock<ConsoleColorer>
{
   ZENMOCK_NONVOID0_CONST(bool, SupportsColor)
   ZENMOCK_VOID1_CONST(SetTextColor, Color)
};

namespace ZenUnit
{
   TESTS(ConsoleColorerTests)
   SPEC(Constructor_SetsFunctionPointers)
   SPECX(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite)
   SPECX(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue)
   SPECX(SupportsColor_ReturnsTrueIfStdoutIsATTY)
#ifdef _WIN32
   SPECX(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor)
#endif
   SPECEND

   unique_ptr<ConsoleColorer> _consoleColorer;
   unique_ptr<const ConsoleColorerSelfMocked> _consoleColorerSelfMocked;

   STARTUP
   {
      _consoleColorer.reset(new ConsoleColorer);
      _consoleColorerSelfMocked.reset(new ConsoleColorerSelfMocked);
   }

   TEST(Constructor_SetsFunctionPointers)
   {
      const ConsoleColorer consoleColorer;
      FUNCTION_TARGETS(::fileno, consoleColorer.fileno_ZenMockable);
      FUNCTION_TARGETS(::isatty, consoleColorer.isatty_ZenMockable);
#ifdef _WIN32
      FUNCTION_TARGETS(::GetStdHandle, consoleColorer.GetStdHandle_ZenMockable);
      FUNCTION_TARGETS(::SetConsoleTextAttribute, consoleColorer.SetConsoleTextAttribute_ZenMockable);
#endif
   }

   TEST4X4(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite,
      Color color, bool expectConsoleSupportsColorCall, bool supportsColorReturnValue, bool expectSetTextColorCallAndExpectedReturnValue,
      Color::White, false, NA<bool>(), false,
      Color::Green, true, false, false,
      Color::Green, true, true, true,
      Color::Red, true, false, false,
      Color::Red, true, true, true)
   {
      if (expectConsoleSupportsColorCall)
      {
         _consoleColorerSelfMocked->SupportsColorMock.ExpectAndReturn(supportsColorReturnValue);
      }
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         _consoleColorerSelfMocked->SetTextColorMock.Expect();
      }
      //
      bool didSetColor = _consoleColorerSelfMocked->SetColor(color);
      //
      if (expectConsoleSupportsColorCall)
      {
         ZEN(_consoleColorerSelfMocked->SupportsColorMock.AssertCalledOnce());
      }
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         ZEN(_consoleColorerSelfMocked->SetTextColorMock.AssertCalledOnceWith(color));
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
         _consoleColorerSelfMocked->SetTextColorMock.Expect();
      }
      //
      _consoleColorerSelfMocked->UnsetColor(didSetTextColor);
      //
      if (expectSetTextColorWhite)
      {
         _consoleColorerSelfMocked->SetTextColorMock.AssertCalledOnceWith(Color::White);
      }
   }

   TEST2X2(SupportsColor_ReturnsTrueIfStdoutIsATTY,
      int isattyReturnValue, bool expectedReturnValue,
      -1, true,
      0, false,
      1, true)
   {
      ZENMOCK_NONVOID1_GLOBAL(int, fileno, FILE*);
      ZENMOCK_NONVOID1_GLOBAL(int, isatty, int);
      const int StdoutFileHandle = 1;
      fileno_ZenMock.ExpectAndReturn(StdoutFileHandle);
      isatty_ZenMock.ExpectAndReturn(isattyReturnValue);
      _consoleColorer->fileno_ZenMockable = ZENBIND1(fileno_ZenMock);
      _consoleColorer->isatty_ZenMockable = ZENBIND1(isatty_ZenMock);
      //
      const bool consoleSupportsColor = _consoleColorer->SupportsColor();
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
      Color::Red, WindowsColor::Red)
   {
      ZENMOCK_NONVOID1_GLOBAL(HANDLE, GetStdHandle, DWORD);
      ZENMOCK_NONVOID2_GLOBAL(BOOL, SetConsoleTextAttribute, HANDLE, WORD);
      _consoleColorer->GetStdHandle_ZenMockable = ZENBIND1(GetStdHandle_ZenMock);
      _consoleColorer->SetConsoleTextAttribute_ZenMockable = ZENBIND2(SetConsoleTextAttribute_ZenMock);

      const HANDLE GetStdHandleReturnValue = HANDLE(1);
      GetStdHandle_ZenMock.ExpectAndReturn(GetStdHandleReturnValue);

      SetConsoleTextAttribute_ZenMock.ExpectAndReturn(TRUE);
      //
      _consoleColorer->SetTextColor(color);
      //
      GetStdHandle_ZenMock.AssertCalledOnceWith(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute_ZenMock.AssertCalledOnceWith(
         GetStdHandleReturnValue, static_cast<WORD>(expectedWindowsColor));
   }
#endif

   }; RUN(ConsoleColorerTests)
}
