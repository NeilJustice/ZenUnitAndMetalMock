#include "pch.h"
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

      const string currentDirectoryPath = _environmentServiceMock->CurrentDirectoryPathMock.ReturnRandom();

      const string machineName = _environmentServiceMock->MachineNameMock.ReturnRandom();

      const string userName = _environmentServiceMock->UserNameMock.ReturnRandom();

      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();

      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();

      const ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      const size_t testRunIndex = ZenUnit::RandomBetween<size_t>(0, 3);
      //
      const string returnedStartTime = _preamblePrinter.PrintPreambleLinesAndGetStartDateTime(zenUnitArgs, testRunIndex, &testClassRunnerRunnerMock);
      //
      const std::string expectedZenUnitVersionLine = "[C++ Unit Testing Framework ZenUnit " + std::string(Version) + "]";
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedZenUnitVersionLine, Color::Green));
      METALMOCK(_consoleMock->WriteColorMock.CalledNTimesWith(8, "[ZenUnit]", Color::Green));
      METALMOCK(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      METALMOCK(_environmentServiceMock->CurrentDirectoryPathMock.CalledOnce());
      METALMOCK(_environmentServiceMock->MachineNameMock.CalledOnce());
      METALMOCK(_environmentServiceMock->UserNameMock.CalledOnce());
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { "     Running: " + zenUnitArgs.commandLine },
         { "   Directory: " + currentDirectoryPath },
         { " MachineName: " + machineName },
         { "    UserName: " + userName },
         { "  RandomSeed: --random-seed=" + to_string(globalZenUnitModeRandomSeed) },
         { " TestClasses: " + to_string(numberOfTestClassesToBeRun) },
         { "   StartTime: " + startDateTime },
         { "     TestRun: " + to_string(testRunIndex + 1) + " of " + to_string(zenUnitArgs.testRuns) + "\n" },
      }));
      ARE_EQUAL(startDateTime, returnedStartTime);
   }

   RUN_TESTS(PreamblePrinterTests)
}
