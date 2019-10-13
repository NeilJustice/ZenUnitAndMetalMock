#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/ZenMock/EnvironmentalistMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/ZenMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   AFACT(Constructor_NewsConsoleAndWatch)
   AFACT(PrintPreambleLinesAndGetStartTime_PrintsCommandLineAndStartTimeAndTestAndTestClassCounts_ReturnsStartTime)
   EVIDENCE

   PreamblePrinter _preamblePrinter;
   const ConsoleMock* _consoleMock = nullptr;
   const WatchMock* _watchMock = nullptr;
   const EnvironmentalistMock* _environmentalistMock = nullptr;

   STARTUP
   {
      _preamblePrinter._environmentalist.reset(_environmentalistMock = new EnvironmentalistMock);
      _preamblePrinter._console.reset(_consoleMock = new ConsoleMock);
      _preamblePrinter._watch.reset(_watchMock = new WatchMock);
   }

   TEST(Constructor_NewsConsoleAndWatch)
   {
      PreamblePrinter preamblePrinter;
      POINTER_WAS_NEWED(preamblePrinter._console);
      POINTER_WAS_NEWED(preamblePrinter._watch);
      POINTER_WAS_NEWED(preamblePrinter._environmentalist);
   }

   TEST(PrintPreambleLinesAndGetStartTime_PrintsCommandLineAndStartTimeAndTestAndTestClassCounts_ReturnsStartTime)
   {
      _consoleMock->WriteLineColorMock.Expect();

      _consoleMock->WriteColorMock.Expect();

      _consoleMock->WriteLineMock.Expect();

      const string currentDirectoryPath = _environmentalistMock->GetCurrentDirectoryPathMock.ReturnRandom();

      const string machineName = _environmentalistMock->GetCurrentMachineNameMock.ReturnRandom();

      const string userName = _environmentalistMock->GetCurrentUserNameMock.ReturnRandom();

      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();

      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();

      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      const string returnedStartTime = _preamblePrinter.PrintPreambleLinesAndGetStartTime(args, &testClassRunnerRunnerMock);
      //
      const std::string expectedZenUnitVersionLine = "[C++ Unit Testing Framework ZenUnit " + std::string(Version::Number()) + "]";
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedZenUnitVersionLine, Color::Green));
      ZENMOCK(_consoleMock->WriteColorMock.CalledNTimesWith(7, "[ZenUnit]", Color::Green));
      ZENMOCK(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetCurrentDirectoryPathMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetCurrentMachineNameMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetCurrentUserNameMock.CalledOnce());
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { "     Running: " + args.commandLine },
         { "   Directory: " + currentDirectoryPath },
         { " MachineName: " + machineName },
         { "    UserName: " + userName },
         { "  RandomSeed: " + to_string(args.randomSeed) },
         { " TestClasses: " + std::to_string(numberOfTestClassesToBeRun) },
         { "   StartTime: " + startDateTime + "\n" }
      }));
      ARE_EQUAL(startDateTime, returnedStartTime);
   }

   RUN_TESTS(PreamblePrinterTests)
}
