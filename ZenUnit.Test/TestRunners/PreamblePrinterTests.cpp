#include "pch.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "Console/Mock/ConsoleMock.h"
#include "Utils/Time/Mock/WatchMock.h"
#include "TestRunners/Mock/TestClassMultiRunnerMock.h"
#include "Utils/Mock/MachineNameGetterMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   SPEC(Constructor_NewsConsoleAndWatch)
   SPECX(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
   SPECEND

   PreamblePrinter _preamblePrinter;
   const MachineNameGetterMock* _machineNameGetterMock;
   const ConsoleMock* _consoleMock;
   const WatchMock* _watchMock;

   STARTUP
   {
      _preamblePrinter._console.reset(_consoleMock = new ConsoleMock);
      _preamblePrinter._watch.reset(_watchMock = new WatchMock);
      _preamblePrinter._machineNameGetter.reset(_machineNameGetterMock = new MachineNameGetterMock);
   }

   TEST(Constructor_NewsConsoleAndWatch)
   {
      PreamblePrinter preamblePrinter;
      CONFIRM_NEWED(preamblePrinter._console);
      CONFIRM_NEWED(preamblePrinter._watch);
      CONFIRM_NEWED(preamblePrinter._machineNameGetter);
   }

   TEST4X4(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts,
      size_t numberOfTestClasses, bool expectTestClassesPlural, Color expectedTextColor, bool expectWriteNewline,
      0ULL, true, Color::Green, false,
      1ULL, false, Color::Green, true,
      1ULL, false, Color::Green, true,
      2ULL, true, Color::Green, true,
      2ULL, true, Color::Green, true)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      if (expectWriteNewline)
      {
         _consoleMock->WriteNewlineMock.Expect();
      }
      TestClassMultiRunnerMock multiTestClassRunnerMock;
      multiTestClassRunnerMock.NumberOfTestClassesMock.ExpectAndReturn(numberOfTestClasses);

      const string TimeZoneDateTimeNow = "TimeZoneDateTimeNow";
      _watchMock->TimeZoneDateTimeNowMock.ExpectAndReturn(TimeZoneDateTimeNow);

      const string MachineName = "MachineName";
      _machineNameGetterMock->GetMachineNameMock.ExpectAndReturn(MachineName);

      const string CommandLine = "CommandLine";
      //
      _preamblePrinter.PrintOpeningThreeLines(&multiTestClassRunnerMock, CommandLine);
      //
      ZEN(_watchMock->TimeZoneDateTimeNowMock.AssertCalledOnce());
      ZEN(multiTestClassRunnerMock.NumberOfTestClassesMock.AssertCalledOnce());
      ZEN(_consoleMock->WriteColorMock.AssertCalledNTimesWith(3, "[ZenUnit]", expectedTextColor));
      ZEN(_machineNameGetterMock->GetMachineNameMock.AssertCalledOnce());
      const string expectedRunningTestClassesLine = String::Concat(
         " Running ", numberOfTestClasses, " test ", expectTestClassesPlural ? "classes" : "class", " on machine ",
         MachineName);
      ZEN(_consoleMock->WriteLineMock.AssertCalls(
      {
         " Running " + CommandLine,
         " Running at " + TimeZoneDateTimeNow,
         expectedRunningTestClassesLine
      }));
      if (expectWriteNewline)
      {
         ZEN(_consoleMock->WriteNewlineMock.AssertCalledOnce());
      }
   }

   }; RUN(PreamblePrinterTests)
}
