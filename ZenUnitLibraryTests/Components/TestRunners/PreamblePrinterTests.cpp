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
      [[maybe_unused]] const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();

      const ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      const size_t testRunIndex = ZenUnit::RandomBetween<size_t>(0, 3);
      //
      const string returnedStartTime =
         _preamblePrinter.PrintPreambleLinesAndGetStartDateTime(zenUnitArgs, testRunIndex, &testClassRunnerRunnerMock);
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledNTimes(8));
      METALMOCK(_consoleMock->WriteColorMock.CalledNTimes(8));

      const std::string expectedZenUnitVersionLine = "[C++ Unit Testing Framework ZenUnit " + std::string(Version) + "]";
      METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedZenUnitVersionLine, Color::Green)).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("     Running: " + zenUnitArgs.commandLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_environmentServiceMock->CurrentDirectoryPathMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("   Directory: " + currentDirectoryPath))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_environmentServiceMock->MachineNameMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(" MachineName: " + machineName))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_environmentServiceMock->UserNameMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("    UserName: " + userName))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("  RandomSeed: --random-seed=" + to_string(globalZenUnitModeRandomSeed)))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(" TestClasses: " + to_string(numberOfTestClassesToBeRun)))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_watchMock->DateTimeNowMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith("   StartTime: " + startDateTime))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith("[ZenUnit]", Color::Green))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(
         "     TestRun: " + to_string(testRunIndex + 1) + " of " + to_string(zenUnitArgs.testRuns) + "\n")));

      ARE_EQUAL(startDateTime, returnedStartTime);
   }

   RUN_TESTS(PreamblePrinterTests)
}
