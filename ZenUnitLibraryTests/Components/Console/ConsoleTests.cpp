#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleColorerMock.h"

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
   const string _message = Random<string>();
#if _WIN32
   ZENMOCK_NONVOID0_FREE(int, _getch)
#endif

   class ConsoleSelfMocked : public Zen::Mock<Console>
   {
   public:
      ZENMOCK_VOID2_CONST(WriteColor, std::string_view, Color)
      ZENMOCK_VOID2_CONST(WriteLineColor, std::string_view, Color)
      ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
      ZENMOCK_VOID0_CONST(WaitForAnyKey)
      ZENMOCK_VOID0_CONST(WriteNewLine)
   } _consoleSelfMocked;

   STARTUP
   {
      _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
#if _WIN32
      _console._call_getch = BIND_0ARG_ZENMOCK_OBJECT(_getchMock);
#endif
   }

   TEST(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   {
      Console console;
      DELETE_TO_ASSERT_NEWED(console._consoleColorer);
      STD_FUNCTION_TARGETS(::exit, console._call_exit);
#if defined _WIN32
      STD_FUNCTION_TARGETS(::IsDebuggerPresent, console._call_IsDebuggerPresent);
      STD_FUNCTION_TARGETS(_getch, console._call_getch);
#endif
   }

   TEST(Write_CallsWriteColorWithWhite)
   {
      _consoleSelfMocked.WriteColorMock.Expect();
      //
      _consoleSelfMocked.Write(_message);
      //
      ZENMOCK(_consoleSelfMocked.WriteColorMock.CalledOnceWith(_message, Color::White));
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
      _console.WriteColor(_message, color);
      //
      ZENMOCK(_consoleColorerMock->SetColorMock.CalledOnceWith(color));
      ZENMOCK(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue));
   }

   TEST(WriteLine_CallsWriteLineWithWhite)
   {
      _consoleSelfMocked.WriteLineColorMock.Expect();
      //
      _consoleSelfMocked.WriteLine(_message);
      //
      ZENMOCK(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith(_message, Color::White));
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
      _console.WriteLineColor(_message, color);
      //
      ZENMOCK(_consoleColorerMock->SetColorMock.CalledOnceWith(color));
      ZENMOCK(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue));
   }

   TEST1X1(WriteLineAndExit_CallsWriteLineAndExit,
      int exitCode,
      0,
      1)
   {
      ZENMOCK_VOID1_FREE(exit, int)
      exitMock.Expect();
      _console._call_exit = BIND_1ARG_ZENMOCK_OBJECT(exitMock);
      //
      _console.WriteLineAndExit(_message, exitCode);
      //
      ZENMOCK(exitMock.CalledOnceWith(exitCode));
   }

   TEST(WriteStringsCommaSeparated_CallsDoWriteStringsCommaSeparated)
   {
      class ConsoleSelfMocked : public Zen::Mock<Console>
      {
      public:
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
      class ConsoleSelfMocked : public Zen::Mock<Console>
      {
      public:
         ZENMOCK_VOID1_CONST(Write, std::string_view)
      } consoleSelfMocked;
      consoleSelfMocked.WriteMock.Expect();
      //
      consoleSelfMocked.DoWriteStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      vector<ZenMock::OneArgumentFunctionCallRef<string_view>> expectedConsoleWriteCalls;
      expectedConsoleWriteCalls.reserve(expectedConsoleWrites.size());
      for (const string& expectedConsoleWrite : expectedConsoleWrites)
      {
         expectedConsoleWriteCalls.emplace_back(expectedConsoleWrite);
      }
      ZENMOCK(consoleSelfMocked.WriteMock.CalledAsFollows(expectedConsoleWriteCalls));
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
         ZENMOCK(_consoleSelfMocked.DebuggerIsPresentMock.CalledOnce());
      }
      if (expectPressAnyKeyAndGetChar)
      {
         ZENMOCK(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith("Press any key to continue . . .", Color::White));
         ZENMOCK(_consoleSelfMocked.WaitForAnyKeyMock.CalledOnce());
      }
   }

#if defined _WIN32
   TEST2X2(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1,
      int isDebuggerPresentReturnValue, bool expectedReturnValue,
      0, false,
      1, true,
      2, false)
   {
      ZENMOCK_NONVOID0_FREE(int, IsDebuggerPresent)
      IsDebuggerPresentMock.Return(isDebuggerPresentReturnValue);
      _console._call_IsDebuggerPresent = BIND_0ARG_ZENMOCK_OBJECT(IsDebuggerPresentMock);
      //
      const bool debuggerIsPresent = _console.DebuggerIsPresent();
      //
      ZENMOCK(IsDebuggerPresentMock.CalledOnce());
      ARE_EQUAL(expectedReturnValue, debuggerIsPresent);
   }
#endif

   TEST(WaitForAnyKey_CallsGetChOnWindows)
   {
#if defined _WIN32
      _getchMock.Return(0);
#endif
      //
      _console.WaitForAnyKey();
      //
#if defined _WIN32
      ZENMOCK(_getchMock.CalledOnce());
#endif
   }

   RUN_TESTS(ConsoleTests)
}
