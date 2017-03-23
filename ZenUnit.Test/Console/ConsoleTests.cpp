#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "Console/Mock/ConsoleColorerMock.h"

namespace ZenUnit
{
   TESTS(ConsoleTests)
   SPEC(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   SPEC(Write_CallsWriteColorWithWhite)
   SPECX(WriteColor_WritesMessageInSpecifiedColor)
   SPEC(WriteLine_CallsWriteLineWithWhite)
   SPECX(WriteLineColor_WritesMessageInSpecifiedColorThenNewline)
   SPECX(WriteLineAndExit_CallsWriteLineAndExit)
   SPECX(PrintStringsCommaSeparated_StartIndexGTEStringsSize_Throws)
   SPECX(PrintStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset)
   SPECX(PauseForAnyKeyIfDebuggerIsPresent_WritesPressAnyKeyAndGetsLineIfDebuggerIsPresent)
#ifdef _WIN32
   SPECX(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1)
#endif
   SPECEND

   Console _console;
   ConsoleColorerMock* _consoleColorerMock;
   const string Message = "Message";

   struct ConsoleSelfMocked : public Zen::Mock<Console>
   {
      ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
      ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
      ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
      ZENMOCK_VOID0_CONST(GetLine)
   } _consoleSelfMocked;

   STARTUP
   {
      _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
   }

   TEST(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   {
      Console console;
      WAS_NEWED(console._consoleColorer);
      FUNCTION_TARGETS(::exit, console.exit_ZenMockable);
   #ifdef _WIN32
      FUNCTION_TARGETS(::IsDebuggerPresent, console.IsDebuggerPresent_ZenMockable);
   #endif
   }

   TEST(Write_CallsWriteColorWithWhite)
   {
      _consoleSelfMocked.WriteColorMock.Expect();
      //
      _consoleSelfMocked.Write(Message);
      //
      ZEN(_consoleSelfMocked.WriteColorMock.AssertCalledOnceWith(Message, Color::White));
   }

   TEST2X2(WriteColor_WritesMessageInSpecifiedColor,
      Color color, bool setColorReturnValue,
      Color::Green, false,
      Color::Green, true,
      Color::Red, false,
      Color::Red, true)
   {
      _consoleColorerMock->SetColorMock.ExpectAndReturn(setColorReturnValue);
      _consoleColorerMock->UnsetColorMock.Expect();
      //
      _console.WriteColor(Message, color);
      //
      ZEN(_consoleColorerMock->SetColorMock.AssertCalledOnceWith(color));
      ZEN(_consoleColorerMock->UnsetColorMock.AssertCalledOnceWith(setColorReturnValue));
   }

   TEST(WriteLine_CallsWriteLineWithWhite)
   {
      _consoleSelfMocked.WriteLineColorMock.Expect();
      //
      _consoleSelfMocked.WriteLine(Message);
      //
      ZEN(_consoleSelfMocked.WriteLineColorMock.AssertCalledOnceWith(Message, Color::White));
   }

   TEST2X2(WriteLineColor_WritesMessageInSpecifiedColorThenNewline,
      Color color, bool setColorReturnValue,
      Color::Green, false,
      Color::Green, true,
      Color::Red, false,
      Color::Red, true)
   {
      _consoleColorerMock->SetColorMock.ExpectAndReturn(setColorReturnValue);
      _consoleColorerMock->UnsetColorMock.Expect();
      //
      _console.WriteLineColor(Message, color);
      //
      ZEN(_consoleColorerMock->SetColorMock.AssertCalledOnceWith(color));
      ZEN(_consoleColorerMock->UnsetColorMock.AssertCalledOnceWith(setColorReturnValue));
   }

   TEST1X1(WriteLineAndExit_CallsWriteLineAndExit,
      int exitCode,
      0,
      1)
   {
      ZENMOCK_VOID1_GLOBAL(exit, int);
      exit_ZenMock.Expect();
      _console.exit_ZenMockable = ZENBIND1(exit_ZenMock);
      //
      _console.WriteLineAndExit(Message, exitCode);
      //
      ZEN(exit_ZenMock.AssertCalledOnceWith(exitCode));
   }

   TEST2X2(PrintStringsCommaSeparated_StartIndexGTEStringsSize_Throws,
      vector<string> strings, size_t startIndex,
      vector<string>{}, 0ull,
      vector<string>{}, 1ull,
      vector<string>{ "Arg1" }, 1ull,
      vector<string>{ "Arg1" }, 2ull)
   {
      THROWS(_console.PrintStringsCommaSeparated(strings, startIndex, 0), invalid_argument,
         "Console::PrintVectorValuesCommaSeparated(): startIndex must be < strings.size(). startIndex=" +
         to_string(startIndex) + ", strings.size(): " + to_string(strings.size()));
   }

   TEST4X4(PrintStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset,
      vector<string> strings, size_t startIndex, size_t numberOfElements, vector<string> expectedConsoleWrites,
      vector<string>{ "Arg1" }, 0ull, 1ull, vector<string>{ "Arg1" },
      vector<string>{ "Arg1", "Arg2" }, 0ull, 2ull, vector<string>{ "Arg1", ", ", "Arg2" },
      vector<string>{ "Arg1", "Arg2" }, 1ull, 1ull, vector<string>{ "Arg2" },
      vector<string>{ "Arg1", "Arg2", "Arg3", "Arg4" }, 2ull, 2ull, vector<string>{ "Arg3", ", ", "Arg4" })
   {
      struct ConsoleSelfMocked : public Zen::Mock<Console>
      {
         ZENMOCK_VOID1_CONST(Write, const string&)
      } consoleSelfMocked;
      consoleSelfMocked.WriteMock.Expect();
      //
      consoleSelfMocked.PrintStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      vector<ZenMock::OneArgCallRef<const string&>> expectedConsoleWriteCalls;
      for (const string& expectedConsoleWrite : expectedConsoleWrites)
      {
         expectedConsoleWriteCalls.emplace_back(expectedConsoleWrite);
      }
      ZEN(consoleSelfMocked.WriteMock.AssertCalls(expectedConsoleWriteCalls));
   }

   TEST2X2(PauseForAnyKeyIfDebuggerIsPresent_WritesPressAnyKeyAndGetsLineIfDebuggerIsPresent,
      bool debuggerIsPresentReturnValue, bool expectPressAnyKeyAndGetLine,
      false, false,
      true, true)
   {
      _consoleSelfMocked.DebuggerIsPresentMock.ExpectAndReturn(debuggerIsPresentReturnValue);
      if (expectPressAnyKeyAndGetLine)
      {
         _consoleSelfMocked.WriteLineColorMock.Expect();
         _consoleSelfMocked.GetLineMock.Expect();
      }
      //
      _consoleSelfMocked.PauseForAnyKeyIfDebuggerIsPresent();
      //
      ZEN(_consoleSelfMocked.DebuggerIsPresentMock.AssertCalledOnce());
      if (expectPressAnyKeyAndGetLine)
      {
         ZEN(_consoleSelfMocked.WriteLineColorMock.AssertCalledOnceWith("Press any key to continue...", Color::White));
         ZEN(_consoleSelfMocked.GetLineMock.AssertCalledOnce());
      }
   }

#ifdef _WIN32
   TEST2X2(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1,
      int isDebuggerPresentReturnValue, bool expectedReturnValue,
      0, false,
      1, true,
      2, false)
   {
      ZENMOCK_NONVOID0_GLOBAL(int, IsDebuggerPresent);
      IsDebuggerPresent_ZenMock.ExpectAndReturn(isDebuggerPresentReturnValue);
      _console.IsDebuggerPresent_ZenMockable = ZENBIND0(IsDebuggerPresent_ZenMock);
      //
      bool debuggerIsPresent = _console.DebuggerIsPresent();
      //
      ZEN(IsDebuggerPresent_ZenMock.AssertCalledOnce());
      ARE_EQUAL(expectedReturnValue, debuggerIsPresent);
   }
#endif

   }; RUN(ConsoleTests)
}
