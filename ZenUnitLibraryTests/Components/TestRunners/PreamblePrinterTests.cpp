#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerRunnerMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
#include "ZenUnitUtilsAndAssertionTests/Components/ZenMock/EnvironmentalistMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/ZenMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(PrintPreambleLinesAndGetStartDateTime_PrintsPreambleLines_ReturnsStartDateTime)
   EVIDENCE

   PreamblePrinter _preamblePrinter;
   const ConsoleMock* _consoleMock = nullptr;
   const EnvironmentalistMock* _environmentalistMock = nullptr;
   const WatchMock* _watchMock = nullptr;

   STARTUP
   {
      _preamblePrinter._console.reset(_consoleMock = new ConsoleMock);
      _preamblePrinter._environmentalist.reset(_environmentalistMock = new EnvironmentalistMock);
      _preamblePrinter._watch.reset(_watchMock = new WatchMock);
   }

   TEST(DefaultConstructor_NewsComponents)
   {
      PreamblePrinter preamblePrinter;
      DELETE_TO_ASSERT_NEWED(preamblePrinter._console);
      DELETE_TO_ASSERT_NEWED(preamblePrinter._environmentalist);
      DELETE_TO_ASSERT_NEWED(preamblePrinter._watch);
   }

   TEST(PrintPreambleLinesAndGetStartDateTime_PrintsPreambleLines_ReturnsStartDateTime)
   {
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();

      const string currentDirectoryPath = _environmentalistMock->GetCurrentDirectoryPathMock.ReturnRandom();

      const string machineName = _environmentalistMock->GetMachineNameMock.ReturnRandom();

      const string userNameRunningThisProgram = _environmentalistMock->GetUserNameRunningThisProgramMock.ReturnRandom();

      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();

      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();

      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      const string returnedStartTime = _preamblePrinter.PrintPreambleLinesAndGetStartDateTime(args, &testClassRunnerRunnerMock);
      //
      const std::string expectedZenUnitVersionLine = "[ZenUnit v" + std::string(Version::Number()) + "]";
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedZenUnitVersionLine, Color::Green));
      ZENMOCK(_consoleMock->WriteColorMock.CalledNTimesWith(7, "[ZenUnit]", Color::Green));
      ZENMOCK(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetCurrentDirectoryPathMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetMachineNameMock.CalledOnce());
      ZENMOCK(_environmentalistMock->GetUserNameRunningThisProgramMock.CalledOnce());
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { "     Running: " + args.commandLine },
         { "   Directory: " + currentDirectoryPath },
         { " MachineName: " + machineName },
         { "    UserName: " + userNameRunningThisProgram },
         { "  RandomSeed: " + to_string(args.randomSeed) },
         { " TestClasses: " + std::to_string(numberOfTestClassesToBeRun) },
         { "   StartTime: " + startDateTime + "\n" }
      }));
      ARE_EQUAL(startDateTime, returnedStartTime);
   }

   RUN_TESTS(PreamblePrinterTests)
}
