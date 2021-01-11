#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestClassRunnerRunnerMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/MetalMock/EnvironmentServiceMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(PrintPreambleLinesAndGetStartDateTime_PrintsPreambleLines_ReturnsStartDateTime)
   EVIDENCE

   PreamblePrinter _preamblePrinter;
   const ConsoleMock* _consoleMock = nullptr;
   const EnvironmentServiceMock* _environmentServiceMock = nullptr;
   const WatchMock* _watchMock = nullptr;

   STARTUP
   {
      _preamblePrinter._console.reset(_consoleMock = new ConsoleMock);
      _preamblePrinter._environmentService.reset(_environmentServiceMock = new EnvironmentServiceMock);
      _preamblePrinter._watch.reset(_watchMock = new WatchMock);
   }

   TEST(DefaultConstructor_NewsComponents)
   {
      PreamblePrinter preamblePrinter;
      DELETE_TO_ASSERT_NEWED(preamblePrinter._console);
      DELETE_TO_ASSERT_NEWED(preamblePrinter._environmentService);
      DELETE_TO_ASSERT_NEWED(preamblePrinter._watch);
   }

   TEST(PrintPreambleLinesAndGetStartDateTime_PrintsPreambleLines_ReturnsStartDateTime)
   {
      _consoleMock->WriteLineColorMock.Expect();
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();

      const string currentDirectoryPath = _environmentServiceMock->GetCurrentDirectoryPathMock.ReturnRandom();

      const string machineName = _environmentServiceMock->GetMachineNameMock.ReturnRandom();

      const string userNameRunningThisProgram = _environmentServiceMock->GetUserNameRunningThisProgramMock.ReturnRandom();

      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();

      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();

      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      //
      const string returnedStartTime = _preamblePrinter.PrintPreambleLinesAndGetStartDateTime(args, &testClassRunnerRunnerMock);
      //
      const std::string expectedZenUnitVersionLine = "[C++ Unit Testing Framework ZenUnit v" + std::string(VersionNumber) + "]";
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedZenUnitVersionLine, Color::Green));
      METALMOCK(_consoleMock->WriteColorMock.CalledNTimesWith(7, "[ZenUnit]", Color::Green));
      METALMOCK(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      METALMOCK(_environmentServiceMock->GetCurrentDirectoryPathMock.CalledOnce());
      METALMOCK(_environmentServiceMock->GetMachineNameMock.CalledOnce());
      METALMOCK(_environmentServiceMock->GetUserNameRunningThisProgramMock.CalledOnce());
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { "     Running: " + args.commandLine },
         { "   Directory: " + currentDirectoryPath },
         { " MachineName: " + machineName },
         { "    UserName: " + userNameRunningThisProgram },
         { "  RandomSeed: --random-seed=" + to_string(globalZenUnitModeRandomSeed) },
         { " TestClasses: " + std::to_string(numberOfTestClassesToBeRun) },
         { "   StartTime: " + startDateTime + "\n" }
      }));
      ARE_EQUAL(startDateTime, returnedStartTime);
   }

   RUN_TESTS(PreamblePrinterTests)
}
