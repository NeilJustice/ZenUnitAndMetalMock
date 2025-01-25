#include "pch.h"

#if defined __linux__
#include <unistd.h>
#elif defined _WIN32
#include <io.h>
// fileno() and isatty() are Linux and Windows wheras _fileno() and _isatty() are Windows only
#pragma warning(disable: 4996) // 'fileno': The POSIX name for this item is deprecated
#endif

namespace ZenUnit
{
   TESTS(ConsoleColorerTests)
   AFACT(DefaultConstructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   FACTS(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite)
   FACTS(SetSupportsColorIfUnset_SetsSupportsColorIfUnset)
   AFACT(SetTextColor_CodeCoverage)
   FACTS(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue)
   FACTS(SupportsColor_ReturnsTrueIfStdoutIsATTY)
#if defined _WIN32
   FACTS(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor)
#endif
   EVIDENCE

   class ConsoleColorer_StandardOutputSupportsColorMocked : public Metal::Mock<ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID0_CONST(bool, StandardOutputSupportsColor)
   };

   class ConsoleColorer_SetCallsMocked : public Metal::Mock<ConsoleColorer>
   {
   public:
      METALMOCK_VOID0_CONST(SetSupportsColorIfUnset)
      METALMOCK_VOID1_CONST(SetTextColor, Color)
   };

   ConsoleColorer _consoleColorer;
   ConsoleColorer_StandardOutputSupportsColorMocked _consoleColorer_StandardOutputSupportsColorMocked;
   ConsoleColorer_SetCallsMocked _consoleColorer_SetCallsMocked;

   TEST(DefaultConstructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   {
      const ConsoleColorer consoleColorer;
      STD_FUNCTION_TARGETS(::fileno, consoleColorer._call_fileno);
      STD_FUNCTION_TARGETS(::isatty, consoleColorer._call_isatty);
#if defined _WIN32
      STD_FUNCTION_TARGETS(::GetStdHandle, consoleColorer._call_GetStdHandle);
      STD_FUNCTION_TARGETS(::SetConsoleTextAttribute, consoleColorer._call_SetConsoleTextAttribute);
#endif
      IS_FALSE(consoleColorer._standardOutputSupportsColor);
      IS_FALSE(consoleColorer._standardOutputSupportsColorSet);
   }

   TEST3X3(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite,
      Color color, bool supportsColor, bool expectSetTextColorCallAndExpectedReturnValue,
      Color::White, false, false,
      Color::White, true, false,
      Color::Green, false, false,
      Color::Green, true, true,
      Color::Red, false, false,
      Color::Red, true, true,
      Color::Red, false, false,
      Color::Teal, true, true)
   {
      _consoleColorer_SetCallsMocked._standardOutputSupportsColor = supportsColor;
      _consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.Expect();
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.Expect();
      }
      //
      const bool didSetColor = _consoleColorer_SetCallsMocked.SetColor(color);
      //
      METALMOCK(_consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.CalledOnce());
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         METALMOCK(_consoleColorer_SetCallsMocked.SetTextColorMock.CalledOnceWith(color));
      }
      ARE_EQUAL(expectSetTextColorCallAndExpectedReturnValue, didSetColor);
   }

   TEST2X2(SetSupportsColorIfUnset_SetsSupportsColorIfUnset,
      bool supportsColorSet, bool expectSupportsColorCall,
      false, true,
      true, false)
   {
      _consoleColorer_StandardOutputSupportsColorMocked._standardOutputSupportsColorSet = supportsColorSet;
      const bool supportsColorReturnValue = ZenUnit::Random<bool>();
      if (expectSupportsColorCall)
      {
         _consoleColorer_StandardOutputSupportsColorMocked.StandardOutputSupportsColorMock.Return(supportsColorReturnValue);
      }
      //
      _consoleColorer_StandardOutputSupportsColorMocked.SetSupportsColorIfUnset();
      //
      if (expectSupportsColorCall)
      {
         METALMOCK(_consoleColorer_StandardOutputSupportsColorMocked.StandardOutputSupportsColorMock.CalledOnce());
         ARE_EQUAL(_consoleColorer_StandardOutputSupportsColorMocked._standardOutputSupportsColor, supportsColorReturnValue);
      }
      IS_TRUE(_consoleColorer_StandardOutputSupportsColorMocked._standardOutputSupportsColorSet);
   }

   TEST(SetTextColor_CodeCoverage)
   {
      const Color color = ZenUnit::RandomEnum<Color>();
      _consoleColorer.SetTextColor(color);
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
         _consoleColorer_SetCallsMocked.SetTextColorMock.CalledOnceWith(Color::White);
      }
   }

   TEST2X2(SupportsColor_ReturnsTrueIfStdoutIsATTY,
      int isattyReturnValue, bool expectedReturnValue,
      -1, true,
      0, false,
      1, true)
   {
      METALMOCK_NONVOID1_STATIC_OR_FREE(int, fileno, FILE*)
      METALMOCK_NONVOID1_STATIC_OR_FREE(int, isatty, int)
      const int StdoutFileHandle = 1;
      filenoMock.Return(StdoutFileHandle);
      isattyMock.Return(isattyReturnValue);
      _consoleColorer._call_fileno = BIND_1ARG_METALMOCK_OBJECT(filenoMock);
      _consoleColorer._call_isatty = BIND_1ARG_METALMOCK_OBJECT(isattyMock);
      //
      const bool consoleSupportsColor = _consoleColorer.StandardOutputSupportsColor();
      //
      METALMOCK(filenoMock.CalledOnceWith(stdout));
      METALMOCK(isattyMock.CalledOnceWith(StdoutFileHandle));
      ARE_EQUAL(expectedReturnValue, consoleSupportsColor);
   }

#if defined _WIN32
   TEST2X2(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor,
      Color color, WindowsColor expectedWindowsColorSet,
      Color::White, WindowsColor::White,
      Color::Green, WindowsColor::Green,
      Color::Red, WindowsColor::Red,
      Color::Teal, WindowsColor::Teal)
   {
      METALMOCK_NONVOID1_STATIC_OR_FREE(HANDLE, GetStdHandle, DWORD)
      METALMOCK_NONVOID2_STATIC_OR_FREE(BOOL, SetConsoleTextAttribute, HANDLE, WORD)
      _consoleColorer._call_GetStdHandle = BIND_1ARG_METALMOCK_OBJECT(GetStdHandleMock);
      _consoleColorer._call_SetConsoleTextAttribute = BIND_2ARG_METALMOCK_OBJECT(SetConsoleTextAttributeMock);
      const HANDLE getStdHandleReturnValue = reinterpret_cast<HANDLE>(1);
      GetStdHandleMock.Return(getStdHandleReturnValue);
      SetConsoleTextAttributeMock.Return(TRUE);
      //
      _consoleColorer.SetTextColor(color);
      //
      METALMOCK(GetStdHandleMock.CalledOnceWith(STD_OUTPUT_HANDLE));
      METALMOCK(SetConsoleTextAttributeMock.CalledOnceWith(getStdHandleReturnValue, static_cast<WORD>(expectedWindowsColorSet)));
   }
#endif

   RUN_TESTS(ConsoleColorerTests)
}
