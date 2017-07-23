#include "pch.h"
#include "Console/Mock/ConsoleMock.h"
#include "TestRunners/Mock/TestClassMultiRunnerMock.h"
#include "Utils/Mock/MachineNameGetterMock.h"
#include "Utils/Time/Mock/WatchMock.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "ZenUnit/Utils/TestRandom.h"

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
      POINTER_WAS_NEWED(preamblePrinter._console);
      POINTER_WAS_NEWED(preamblePrinter._watch);
      POINTER_WAS_NEWED(preamblePrinter._machineNameGetter);
   }

   TEST4X4(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts,
      size_t numberOfTestClasses, bool expectTestClassesPlural, Color expectedTextColor, bool expectWriteNewLine,
      size_t(0), true, Color::Green, false,
      size_t(1), false, Color::Green, true,
      size_t(1), false, Color::Green, true,
      size_t(2), true, Color::Green, true,
      size_t(2), true, Color::Green, true)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      if (expectWriteNewLine)
      {
         _consoleMock->WriteNewLineMock.Expect();
      }
      TestClassMultiRunnerMock multiTestClassRunnerMock;
      multiTestClassRunnerMock.NumberOfTestClassesMock.ExpectAndReturn(numberOfTestClasses);

      const string TimeZoneDateTimeNow = TestRandom<string>();
      _watchMock->TimeZoneDateTimeNowMock.ExpectAndReturn(TimeZoneDateTimeNow);

      const string MachineName = TestRandom<string>();
      _machineNameGetterMock->GetMachineNameMock.ExpectAndReturn(MachineName);

      const string CommandLine = TestRandom<string>();
      //
      _preamblePrinter.PrintOpeningThreeLines(CommandLine, &multiTestClassRunnerMock);
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
      if (expectWriteNewLine)
      {
         ZEN(_consoleMock->WriteNewLineMock.AssertCalledOnce());
      }
   }

   }; RUN(PreamblePrinterTests)
}
