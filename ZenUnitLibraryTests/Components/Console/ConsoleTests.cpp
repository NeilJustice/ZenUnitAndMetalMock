#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleColorerMock.h"

namespace ZenUnit
{
   TESTS(ConsoleTests)
   AFACT(DefaultConstructor_SetsFunctionPointers_NewsConsoleColorer)
   FACTS(MicrosecondsToTwoDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces)
   AFACT(Write_WritesMessageToCout)
   FACTS(WriteColor_WritesMessageInSpecifiedColor)
   AFACT(WriteLine_CallsWriteLineWithWhite)
   FACTS(WriteLineColor_WritesMessageInSpecifiedColorThenNewLine)
   FACTS(WriteLineAndExit_CallsWriteLineAndExit)
   AFACT(WriteNewLineIfValuesAreNotEqual_ValuesAreEqual_DoesNotThrowException)
   AFACT(WriteNewLineIfValuesAreNotEqual_ValuesAreNotEqual_WritesNewLine)
   AFACT(WriteStringsCommaSeparated_CallsDoWriteStringsCommaSeparated)
   FACTS(WaitForEnterKeyIfDebuggerPresentOrValueTrue_WritesPressAnyKeyAndGetsCharIfDebuggerPresentOrValueTrue)
   AFACT(WaitForEnterKey_CallsGetCharFromStandardInputUntilNewline)
#if defined _WIN32
   FACTS(DebuggerIsPresentOnWindows_ReturnsTrueIfIsDebuggerPresentFunctionReturns1)
#endif
   AFACT(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset__TestCase1)
   AFACT(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset__TestCase2)
   EVIDENCE

   Console _console;
   // Function Pointers
   METALMOCK_VOID1_FREE(_call_quick_exit, int)
   METALMOCK_NONVOID0_FREE(int, _call_GetCharFromStandardInput)
#if defined _WIN32
   METALMOCK_NONVOID0_FREE(int, _call_IsDebuggerPresent)
#endif
   // Mutable Components
   ConsoleColorerMock* _consoleColorerMock = nullptr;

   const string _message = Random<string>();

   class ConsoleSelfMocked : public Metal::Mock<Console>
   {
   public:
      METALMOCK_VOID2_CONST(WriteColor, std::string_view, Color)
      METALMOCK_VOID2_CONST(WriteLineColor, std::string_view, Color)
      METALMOCK_NONVOID0_CONST(bool, DebuggerIsPresentOnWindows)
      METALMOCK_VOID0_CONST(WaitForEnterKey)
      METALMOCK_VOID0_CONST(WriteNewLine)
   } _consoleSelfMocked;

   STARTUP
   {
      // Function Pointers
      _console._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
      _console._call_GetCharFromStandardInput = BIND_0ARG_METALMOCK_OBJECT(_call_GetCharFromStandardInputMock);
#if defined _WIN32
      _console._call_IsDebuggerPresent = BIND_0ARG_METALMOCK_OBJECT(_call_IsDebuggerPresentMock);
#endif
      // Mutable Components
      _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
   }

   TEST(DefaultConstructor_SetsFunctionPointers_NewsConsoleColorer)
   {
      Console console;
      // Function Pointers
      STD_FUNCTION_TARGETS(::quick_exit, console._call_quick_exit);
      STD_FUNCTION_TARGETS(Console::GetCharFromStandardInput, console._call_GetCharFromStandardInput);
#if defined _WIN32
      STD_FUNCTION_TARGETS(::IsDebuggerPresent, console._call_IsDebuggerPresent);
#endif
      // Mutable Components
      DELETE_TO_ASSERT_NEWED(console._consoleColorer);
   }

   TEST2X2(MicrosecondsToTwoDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces,
      unsigned microseconds, const string& expectedReturnValue,
      0U, "[0.00ms]",
      1U, "[0.00ms]",
      2U, "[0.00ms]",
      10U, "[0.01ms]",
      12U, "[0.01ms]",
      100U, "[0.10ms]",
      120U, "[0.12ms]",
      123U, "[0.12ms]",
      1000U, "[1.00ms]",
      1234U, "[1.23ms]",
      12345U, "[12.35ms]",
      123456U, "[123.46ms]",
      1234567U, "[1234.57ms]",
      12345678U, "[12345.68ms]",
      123456789U, "[123456.79ms]",
      1234567890U, "[1234567.89ms]")
   {
      const string twoDecimalPlaceMillisecondsString = _console.MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
      ARE_EQUAL(expectedReturnValue, twoDecimalPlaceMillisecondsString);
   }

   TEST(Write_WritesMessageToCout)
   {
      _consoleSelfMocked.Write(_message);
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
      METALMOCKTHEN(_consoleColorerMock->SetColorMock.CalledOnceWith(color)).Then(
      METALMOCKTHEN(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue)));
   }

   TEST(WriteLine_CallsWriteLineWithWhite)
   {
      _consoleSelfMocked.WriteLineColorMock.Expect();
      //
      _consoleSelfMocked.WriteLine(_message);
      //
      METALMOCK(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith(_message, Color::White));
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
      METALMOCKTHEN(_consoleColorerMock->SetColorMock.CalledOnceWith(color)).Then(
      METALMOCKTHEN(_consoleColorerMock->UnsetColorMock.CalledOnceWith(setColorReturnValue)));
   }

   TEST1X1(WriteLineAndExit_CallsWriteLineAndExit,
      int exitCode,
      0,
      1)
   {
      _call_quick_exitMock.Expect();
      //
      _console.WriteLineAndExit(_message, exitCode);
      //
      METALMOCK(_call_quick_exitMock.CalledOnceWith(exitCode));
   }

   TEST(WriteNewLineIfValuesAreNotEqual_ValuesAreEqual_DoesNotThrowException)
   {
      const size_t value1 = ZenUnit::Random<size_t>();
      const size_t value2 = value1;
      //
      _consoleSelfMocked.WriteNewLineIfValuesAreNotEqual(value1, value2);
   }

   TEST(WriteNewLineIfValuesAreNotEqual_ValuesAreNotEqual_WritesNewLine)
   {
      _consoleSelfMocked.WriteNewLineMock.Expect();
      const size_t value1 = ZenUnit::Random<size_t>();
      const size_t value2 = ZenUnit::RandomNotEqualTo<size_t>(value1);
      //
      _consoleSelfMocked.WriteNewLineIfValuesAreNotEqual(value1, value2);
      //
      METALMOCK(_consoleSelfMocked.WriteNewLineMock.CalledOnce());
   }

   TEST(WriteStringsCommaSeparated_CallsDoWriteStringsCommaSeparated)
   {
      class ConsoleSelfMocked : public Metal::Mock<Console>
      {
      public:
         METALMOCK_VOID3_CONST(DoWriteStringsCommaSeparated, const vector<string>&, size_t, size_t)
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

   TEST3X3(WaitForEnterKeyIfDebuggerPresentOrValueTrue_WritesPressAnyKeyAndGetsCharIfDebuggerPresentOrValueTrue,
      bool doWait, bool debuggerIsPresent, bool expectPressAnyKeyAndGetChar,
      false, false, false,
      false, true, true,
      true, false, true,
      true, true, true)
   {
      if (!doWait)
      {
         _consoleSelfMocked.DebuggerIsPresentOnWindowsMock.Return(debuggerIsPresent);
      }
      if (expectPressAnyKeyAndGetChar)
      {
         _consoleSelfMocked.WriteLineColorMock.Expect();
         _consoleSelfMocked.WaitForEnterKeyMock.Expect();
      }
      //
      _consoleSelfMocked.WaitForEnterKeyIfDebuggerPresentOrValueTrue(doWait);
      //
      if (!doWait)
      {
         METALMOCK(_consoleSelfMocked.DebuggerIsPresentOnWindowsMock.CalledOnce());
      }
      if (expectPressAnyKeyAndGetChar)
      {
         METALMOCKTHEN(_consoleSelfMocked.WriteLineColorMock.CalledOnceWith("Press enter to continue...", Color::White)).Then(
         METALMOCKTHEN(_consoleSelfMocked.WaitForEnterKeyMock.CalledOnce()));
      }
   }

   TEST(WaitForEnterKey_CallsGetCharFromStandardInputUntilNewline)
   {
      _call_GetCharFromStandardInputMock.ReturnValues('a', 'b', '\n', 'c');
      //
      _console.WaitForEnterKey();
      //
      METALMOCK(_call_GetCharFromStandardInputMock.CalledNTimes(3));
   }

#if defined _WIN32
   TEST2X2(DebuggerIsPresentOnWindows_ReturnsTrueIfIsDebuggerPresentFunctionReturns1,
      int isDebuggerPresentReturnValue, bool expectedReturnValue,
      0, false,
      1, true,
      2, false)
   {
      _call_IsDebuggerPresentMock.Return(isDebuggerPresentReturnValue);
      //
      const bool debuggerIsPresentOnWindows = _console.DebuggerIsPresentOnWindows();
      //
      METALMOCK(_call_IsDebuggerPresentMock.CalledOnce());
      ARE_EQUAL(expectedReturnValue, debuggerIsPresentOnWindows);
   }
#endif

   class ConsoleWithWriteSelfMocked : public Metal::Mock<Console>
   {
   public:
      METALMOCK_VOID1_CONST(Write, std::string_view)
   } _consoleWithWriteSelfMocked;

   TEST(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset__TestCase1)
   {
      const vector<string> strings = vector<string>{ "Argument1" };
      const size_t startIndex = 0;
      const size_t numberOfElements = 1;
      //
      _consoleWithWriteSelfMocked.WriteMock.Expect();
      //
      _consoleWithWriteSelfMocked.DoWriteStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      METALMOCK(_consoleWithWriteSelfMocked.WriteMock.CalledOnceWith("Argument1"));
   }

   TEST(DoWriteStringsCommaSeparated_PrintsCommaSeparatedLengthNumberOfVectorValuesAtSpecifiedOffset__TestCase2)
   {
      const vector<string> strings = { "Argument1", "Argument2", "Argument3", "Argument4" };
      const size_t startIndex = 1;
      const size_t numberOfElements = 3;
      _consoleWithWriteSelfMocked.WriteMock.Expect();
      //
      _consoleWithWriteSelfMocked.DoWriteStringsCommaSeparated(strings, startIndex, numberOfElements);
      //
      METALMOCK(_consoleWithWriteSelfMocked.WriteMock.CalledNTimes(5));
      METALMOCKTHEN(_consoleWithWriteSelfMocked.WriteMock.CalledWith("Argument2")).Then(
      METALMOCKTHEN(_consoleWithWriteSelfMocked.WriteMock.CalledWith(", "))).Then(
      METALMOCKTHEN(_consoleWithWriteSelfMocked.WriteMock.CalledWith("Argument3"))).Then(
      METALMOCKTHEN(_consoleWithWriteSelfMocked.WriteMock.CalledWith(", "))).Then(
      METALMOCKTHEN(_consoleWithWriteSelfMocked.WriteMock.CalledWith("Argument3")));
   }

   RUN_TESTS(ConsoleTests)
}
