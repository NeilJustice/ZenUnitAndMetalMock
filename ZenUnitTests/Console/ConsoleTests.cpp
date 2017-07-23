#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Utils/TestRandom.h"
#include "ZenUnitTests/Console/Mock/ConsoleColorerMock.h"

namespace ZenUnit
{
   TESTS(ConsoleTests)
   SPEC(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   SPEC(Write_CallsWriteColorWithWhite)
   SPECX(NonLaconicWrite_CallsWriteColorIfPrintModeNotLaconic)
   SPECX(WriteColor_WritesMessageInSpecifiedColor)
   SPECX(NonLaconicWriteColor_CallsWriteColorIfPrintModeNotLaconic)
   SPEC(WriteLine_CallsWriteLineWithWhite)
   SPECX(NonLaconicWriteNewLine_CallsWriteLineWithWhite)
   SPECX(NonLaconicWriteLine_CallsWriteLineIfPrintModeNotLaconic)
   SPECX(WriteLineColor_WritesMessageInSpecifiedColorThenNewLine)
   SPECX(WriteLineAndExit_CallsWriteLineAndExit)
   SPEC(NonLaconicWriteStringsCommaSeparated_PrintModeLaconic_DoesNothing)
   SPECX(NonLaconicWriteStringsCommaSeparated_PrintModeNotLaconic_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset)
   SPECX(PauseForAnyKeyIfDebuggerIsPresent_WritesPressAnyKeyAndGetsLineIfDebuggerIsPresent)
#ifdef _WIN32
   SPECX(DebuggerIsPresent_ReturnsTrueIfIsDebuggerPresentFunctionReturns1)
#endif
   SPECEND

   Console _console;
   ConsoleColorerMock* _consoleColorerMock;
   const string Message = TestRandom<string>();

   struct ConsoleSelfMocked : public Zen::Mock<Console>
   {
      ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
      ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
      ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
      ZENMOCK_VOID0_CONST(GetLine)
      ZENMOCK_VOID0_CONST(WriteNewLine)
   } _consoleSelfMocked;

   STARTUP
   {
      _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
   }

   TEST(Constructor_NewsConsoleColorer_SetsFunctionPointers)
   {
      Console console;
      POINTER_WAS_NEWED(console._consoleColorer);
      STD_FUNCTION_TARGETS(::exit, console._exit_ZenMockable);
   #ifdef _WIN32
      STD_FUNCTION_TARGETS(::IsDebuggerPresent, console._IsDebuggerPresent_ZenMockable);
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

   TEST2X2(NonLaconicWrite_CallsWriteColorIfPrintModeNotLaconic,
      PrintMode printMode, bool expectWriteCall,
      PrintMode::Laconic, false,
      PrintMode::Default, true,
      PrintMode::Verbose, true)
   {
      struct ConsoleSelfMock_Write : public Zen::Mock<Console>
      {
         ZENMOCK_VOID1_CONST(Write, const string&)
      } consoleSelfMock_Write;
      if (expectWriteCall)
      {
         consoleSelfMock_Write.WriteMock.Expect();
      }
      //
      consoleSelfMock_Write.NonLaconicWrite(Message, printMode);
      //
      if (expectWriteCall)
      {
         ZEN(consoleSelfMock_Write.WriteMock.AssertCalledOnceWith(Message));
      }
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

   TEST2X2(NonLaconicWriteColor_CallsWriteColorIfPrintModeNotLaconic,
      PrintMode printMode, bool expectWriteColorCall,
      PrintMode::Laconic, false,
      PrintMode::Default, true,
      PrintMode::Verbose, true)
   {
      struct ConsoleSelfMock_WriteColor : public Zen::Mock<Console>
      {
         ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
      } consoleSelfMock_WriteColor;
      if (expectWriteColorCall)
      {
         consoleSelfMock_WriteColor.WriteColorMock.Expect();
      }
      //
      consoleSelfMock_WriteColor.NonLaconicWriteColor(Message, Color::Green, printMode);
      //
      if (expectWriteColorCall)
      {
         ZEN(consoleSelfMock_WriteColor.WriteColorMock.AssertCalledOnceWith(Message, Color::Green));
      }
   }

   TEST(WriteLine_CallsWriteLineWithWhite)
   {
      _consoleSelfMocked.WriteLineColorMock.Expect();
      //
      _consoleSelfMocked.WriteLine(Message);
      //
      ZEN(_consoleSelfMocked.WriteLineColorMock.AssertCalledOnceWith(Message, Color::White));
   }

   TEST2X2(NonLaconicWriteNewLine_CallsWriteLineWithWhite,
      PrintMode printMode, bool expectWriteNewLineCall,
      PrintMode::Laconic, false,
      PrintMode::Default, true,
      PrintMode::Verbose, true)
   {
      if (expectWriteNewLineCall)
      {
         _consoleSelfMocked.WriteNewLineMock.Expect();
      }
      //
      _consoleSelfMocked.NonLaconicWriteNewLine(printMode);
      //
      if (expectWriteNewLineCall)
      {
         ZEN(_consoleSelfMocked.WriteNewLineMock.AssertCalledOnce());
      }
   }

   TEST2X2(NonLaconicWriteLine_CallsWriteLineIfPrintModeNotLaconic,
      PrintMode printMode, bool expectWriteLineCall,
      PrintMode::Laconic, false,
      PrintMode::Default, true,
      PrintMode::Verbose, true)
   {
      struct ConsoleSelfMock_WriteColor : public Zen::Mock<Console>
      {
         ZENMOCK_VOID1_CONST(WriteLine, const string&)
      } consoleSelfMock_WriteLine;
      if (expectWriteLineCall)
      {
         consoleSelfMock_WriteLine.WriteLineMock.Expect();
      }
      //
      consoleSelfMock_WriteLine.NonLaconicWriteLine(Message, printMode);
      //
      if (expectWriteLineCall)
      {
         ZEN(consoleSelfMock_WriteLine.WriteLineMock.AssertCalledOnceWith(Message));
      }
   }

   TEST2X2(WriteLineColor_WritesMessageInSpecifiedColorThenNewLine,
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
      ZENMOCK_VOID1_FREE(exit, int);
      exit_ZenMock.Expect();
      _console._exit_ZenMockable = ZENBIND1(exit_ZenMock);
      //
      _console.WriteLineAndExit(Message, exitCode);
      //
      ZEN(exit_ZenMock.AssertCalledOnceWith(exitCode));
   }

   TEST(NonLaconicWriteStringsCommaSeparated_PrintModeLaconic_DoesNothing)
   {
      _console.NonLaconicWriteStringsCommaSeparated({ "" }, 0, 0, PrintMode::Laconic);
   }

   TEST5X5(NonLaconicWriteStringsCommaSeparated_PrintModeNotLaconic_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset,
      PrintMode printMode, const vector<string>& strings, size_t startIndex, size_t numberOfElements, const vector<string>& expectedConsoleWrites,
      PrintMode::Default, vector<string>{ "Arg1" }, size_t(0), size_t(1), vector<string>{ "Arg1" },
      PrintMode::Default, vector<string>{ "Arg1", "Arg2" }, size_t(0), size_t(2), vector<string>{ "Arg1", ", ", "Arg2" },
      PrintMode::Default, vector<string>{ "Arg1", "Arg2" }, size_t(1), size_t(1), vector<string>{ "Arg2" },
      PrintMode::Default, vector<string>{ "Arg1", "Arg2", "Arg3", "Arg4" }, size_t(2), size_t(2), vector<string>{ "Arg3", ", ", "Arg4" },

      PrintMode::Verbose, vector<string>{ "Arg1" }, size_t(0), size_t(1), vector<string>{ "Arg1" },
      PrintMode::Verbose, vector<string>{ "Arg1", "Arg2" }, size_t(0), size_t(2), vector<string>{ "Arg1", ", ", "Arg2" },
      PrintMode::Verbose, vector<string>{ "Arg1", "Arg2" }, size_t(1), size_t(1), vector<string>{ "Arg2" },
      PrintMode::Verbose, vector<string>{ "Arg1", "Arg2", "Arg3", "Arg4" }, size_t(2), size_t(2), vector<string>{ "Arg3", ", ", "Arg4" })
   {
      struct ConsoleSelfMocked : public Zen::Mock<Console>
      {
         ZENMOCK_VOID1_CONST(Write, const string&)
      } consoleSelfMocked;
      consoleSelfMocked.WriteMock.Expect();
      //
      consoleSelfMocked.NonLaconicWriteStringsCommaSeparated(strings, startIndex, numberOfElements, printMode);
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
      ZENMOCK_NONVOID0_FREE(int, IsDebuggerPresent);
      IsDebuggerPresent_ZenMock.ExpectAndReturn(isDebuggerPresentReturnValue);
      _console._IsDebuggerPresent_ZenMockable = ZENBIND0(IsDebuggerPresent_ZenMock);
      //
      const bool debuggerIsPresent = _console.DebuggerIsPresent();
      //
      ZEN(IsDebuggerPresent_ZenMock.AssertCalledOnce());
      ARE_EQUAL(expectedReturnValue, debuggerIsPresent);
   }
#endif

   }; RUN(ConsoleTests)
}
