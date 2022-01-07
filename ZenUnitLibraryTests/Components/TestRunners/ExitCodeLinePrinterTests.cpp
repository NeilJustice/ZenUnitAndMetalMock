#include "pch.h"

namespace ZenUnit
{
   TESTS(ExitCodeLinePrinterTests)
   AFACT(DefaultConstructor_NewsConsole)
   AFACT(PrintExitCodeLine_AlwaysExit0IsTrue_PrintExitCode0InGreenRegardlessOfZenUnitExitCode)
   AFACT(PrintExitCodeLine_AlwaysExit0IsFalse_ZenUnitExitCodeIs0_PrintsExitCode0InGreen)
   AFACT(PrintExitCodeLine_AlwaysExit0IsFalse_ZenUnitExitCodeIsNot0_PrintsExitCodeInRed)
   EVIDENCE

   ExitCodeLinePrinter _exitCodeLinePrinter;
   // Constant Components
   ConsoleMock* _consoleMock = nullptr;

   STARTUP
   {
      // Constant Components
      _exitCodeLinePrinter._console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(DefaultConstructor_NewsConsole)
   {
      ExitCodeLinePrinter exitCodeLinePrinter;
      // Constant Components
      DELETE_TO_ASSERT_NEWED(exitCodeLinePrinter._console);
   }

   TEST(PrintExitCodeLine_AlwaysExit0IsTrue_PrintExitCode0InGreenRegardlessOfZenUnitExitCode)
   {
      const int zenUnitExitCode = ZenUnit::Random<int>();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      //
      _exitCodeLinePrinter.PrintExitCodeLine(zenUnitExitCode, true);
      //
      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit]", Color::Green));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith("   ExitCode: 0"));
   }

   TEST(PrintExitCodeLine_AlwaysExit0IsFalse_ZenUnitExitCodeIs0_PrintsExitCode0InGreen)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      //
      _exitCodeLinePrinter.PrintExitCodeLine(0, false);
      //
      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit]", Color::Green));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith("   ExitCode: 0"));
   }

   TEST(PrintExitCodeLine_AlwaysExit0IsFalse_ZenUnitExitCodeIsNot0_PrintsExitCodeInRed)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      const int zenUnitExitCode = ZenUnit::RandomNotEqualTo<int>(0);
      //
      _exitCodeLinePrinter.PrintExitCodeLine(zenUnitExitCode, false);
      //
      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith(">>------>", Color::Red));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith("   ExitCode: " + to_string(zenUnitExitCode)));
   }

   RUN_TESTS(ExitCodeLinePrinterTests)
}
