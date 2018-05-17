#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleColorerMock.h"

namespace ZenUnit
{
   TESTS(ConsoleTests)
   AFACT(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   AFACT(Write_CallsWriteColorWithWhite)
   FACTS(WriteColor_WritesMessageInSpecifiedColor)
   AFACT(WriteLine_CallsWriteLineWithWhite)
   FACTS(WriteLineColor_WritesMessageInSpecifiedColorThenNewLine)
   FACTS(WriteLineAndExit_CallsWriteLineAndExit)
   AFACT(WriteStringsCommaSeparated_CallsDoWriteStringsCommaSeparated)
   FACTS(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset)
   FACTS(WaitForAnyKeyIfDebuggerPresentOrValueTrue_WritesPressAnyKeyAndGetsCharIfDebuggerPresentOrValueTrue)
#if defined _WIN32
   FACTS(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1)
#endif
   AFACT(WaitForAnyKey_CallsGetChOnWindows)
   EVIDENCE

   Console _console;
   ConsoleColorerMock* _consoleColorerMock = nullptr;
   const string Message = Random<string>();
#if _WIN32
   ZENMOCK_NONVOID0_GLOBAL(int, _getch);
#endif

   struct ConsoleSelfMocked : public Zen::Mock<Console>
   {
      ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
      ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
      ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
      ZENMOCK_VOID0_CONST(WaitForAnyKey)
      ZENMOCK_VOID0_CONST(WriteNewLine)
   } _consoleSelfMocked;

   STARTUP
   {
      _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
#if _WIN32
      _console.call_getch = BIND_0ARG_ZENMOCK_OBJECT(_getch_ZenMockObject);
#endif
   }

   TEST(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   {
      Console console;
      POINTER_WAS_NEWED(console._consoleColorer);
      STD_FUNCTION_TARGETS(::exit, console.call_exit);
#if defined _WIN32
      STD_FUNCTION_TARGETS(::IsDebuggerPresent, console.call_IsDebuggerPresent);
      STD_FUNCTION_TARGETS(_getch, console.call_getch);
#endif
   }

   TEST(Write_CallsWriteColorWithWhite)
   {
      _consoleSelfMocked.WriteColorMock.Expect();
      //
      _consoleSelfMocked.Write(Message);
      //
      ZEN(_consoleSelfMocked.WriteColorMock.CalledOnceWith(Message, Color::White));
   }

   TEST2X2(WriteColor_WritesMessageInSpecifiedColor,
      Color color, bool setColorReturnValue,
      Color::Green, false,
      Color::Green, true,
      Color::Red, false,
      Color::Red, true,
      Color::Teal, false,
      Color::Teal, true)
   {
      _consoleColorerMock->SetColorMock.Return(setColorReturnValue);
      _consoleColorerMock->UnsetColorMock.Expect();
      //
      _console.WriteColor(Message, color);
      //
      ZEN(_consoleColorerMock->SetColorMock.CalledOnceWith(color));
      ZEN(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue));
   }

   TEST(WriteLine_CallsWriteLineWithWhite)
   {
      _consoleSelfMocked.WriteLineColorMock.Expect();
      //
      _consoleSelfMocked.WriteLine(Message);
      //
      ZEN(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith(Message, Color::White));
   }

   TEST2X2(WriteLineColor_WritesMessageInSpecifiedColorThenNewLine,
      Color color, bool setColorReturnValue,
      Color::Green, false,
      Color::Green, true,
      Color::Red, false,
      Color::Red, true,
      Color::Teal, false,
      Color::Teal, true)
   {
      _consoleColorerMock->SetColorMock.Return(setColorReturnValue);
      _consoleColorerMock->UnsetColorMock.Expect();
      //
      _console.WriteLineColor(Message, color);
      //
      ZEN(_consoleColorerMock->SetColorMock.CalledOnceWith(color));
      ZEN(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue));
   }

   TEST1X1(WriteLineAndExit_CallsWriteLineAndExit,
      int exitCode,
      0,
      1)
   {
      ZENMOCK_VOID1_GLOBAL(exit, int);
      exit_ZenMockObject.Expect();
      _console.call_exit = BIND_1ARG_ZENMOCK_OBJECT(exit_ZenMockObject);
      //
      _console.WriteLineAndExit(Message, exitCode);
      //
      ZEN(exit_ZenMockObject.CalledOnceWith(exitCode));
   }

   TEST(WriteStringsCommaSeparated_CallsDoWriteStringsCommaSeparated)
   {
      struct ConsoleSelfMocked : public Zen::Mock<Console>
      {
         ZENMOCK_VOID3_CONST(DoWriteStringsCommaSeparated, const vector<string>&, size_t, size_t)
      } consoleSelfMocked;
      vector<string> strings = { Random<string>() };
      const size_t startIndex = Random<size_t>();
      const size_t numberOfElements = Random<size_t>();
      consoleSelfMocked.DoWriteStringsCommaSeparatedMock.Expect();
      //
      consoleSelfMocked.WriteStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      consoleSelfMocked.DoWriteStringsCommaSeparatedMock.CalledOnceWith(strings, startIndex, numberOfElements);
   }

   TEST4X4(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset,
      const vector<string>& strings, size_t startIndex, size_t numberOfElements, const vector<string>& expectedConsoleWrites,
      vector<string>{ "Argument1" }, size_t(0), size_t(1), vector<string>{ "Argument1" },
      vector<string>{ "Argument1", "Argument2" }, size_t(0), size_t(2), vector<string>{ "Argument1", ", ", "Argument2" },
      vector<string>{ "Argument1", "Argument2" }, size_t(1), size_t(1), vector<string>{ "Argument2" },
      vector<string>{ "Argument1", "Argument2", "Argument3", "Argument4" }, size_t(2), size_t(2), vector<string>{ "Argument3", ", ", "Argument4" })
   {
      struct ConsoleSelfMocked : public Zen::Mock<Console>
      {
         ZENMOCK_VOID1_CONST(Write, const string&)
      } consoleSelfMocked;
      consoleSelfMocked.WriteMock.Expect();
      //
      consoleSelfMocked.DoWriteStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      vector<ZenMock::OneArgumentCallRef<const string&>> expectedConsoleWriteCalls;
      expectedConsoleWriteCalls.reserve(expectedConsoleWrites.size());
      for (const string& expectedConsoleWrite : expectedConsoleWrites)
      {
         expectedConsoleWriteCalls.emplace_back(expectedConsoleWrite);
      }
      ZEN(consoleSelfMocked.WriteMock.CalledAsFollows(expectedConsoleWriteCalls));
   }

   TEST3X3(WaitForAnyKeyIfDebuggerPresentOrValueTrue_WritesPressAnyKeyAndGetsCharIfDebuggerPresentOrValueTrue,
      bool doWait, bool debuggerIsPresent, bool expectPressAnyKeyAndGetChar,
      false, false, false,
      false, true, true,
      true, false, true,
      true, true, true)
   {
      if (!doWait)
      {
         _consoleSelfMocked.DebuggerIsPresentMock.Return(debuggerIsPresent);
      }
      if (expectPressAnyKeyAndGetChar)
      {
         _consoleSelfMocked.WriteLineColorMock.Expect();
         _consoleSelfMocked.WaitForAnyKeyMock.Expect();
      }
      //
      _consoleSelfMocked.WaitForAnyKeyIfDebuggerPresentOrValueTrue(doWait);
      //
      if (!doWait)
      {
         ZEN(_consoleSelfMocked.DebuggerIsPresentMock.CalledOnce());
      }
      if (expectPressAnyKeyAndGetChar)
      {
         ZEN(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith("Press any key to continue . . .", Color::White));
         ZEN(_consoleSelfMocked.WaitForAnyKeyMock.CalledOnce());
      }
   }

#if defined _WIN32
   TEST2X2(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1,
      int isDebuggerPresentReturnValue, bool expectedReturnValue,
      0, false,
      1, true,
      2, false)
   {
      ZENMOCK_NONVOID0_GLOBAL(int, IsDebuggerPresent);
      IsDebuggerPresent_ZenMockObject.Return(isDebuggerPresentReturnValue);
      _console.call_IsDebuggerPresent = BIND_0ARG_ZENMOCK_OBJECT(IsDebuggerPresent_ZenMockObject);
      //
      const bool debuggerIsPresent = _console.DebuggerIsPresent();
      //
      ZEN(IsDebuggerPresent_ZenMockObject.CalledOnce());
      ARE_EQUAL(expectedReturnValue, debuggerIsPresent);
   }
#endif

   TEST(WaitForAnyKey_CallsGetChOnWindows)
   {
#ifdef _WIN32
      _getch_ZenMockObject.Return(0);
#endif
      //
      _console.WaitForAnyKey();
      //
#ifdef _WIN32
      ZEN(_getch_ZenMockObject.CalledOnce());
#endif
   }

   RUN_TESTS(ConsoleTests)
}
