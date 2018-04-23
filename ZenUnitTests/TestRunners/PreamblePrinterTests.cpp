#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerRunnerMock.h"
#include "ZenUnitTests/Utils/Mock/MachineNameGetterMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   AFACT(Constructor_NewsConsoleAndWatch)
   AFACT(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
   FACTS(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName)
   FACTS(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString)
   EVIDENCE

   struct PreamblePrinterSelfMocked : public Zen::Mock<PreamblePrinter>
   {
      const ConsoleMock* consoleMock;
      const WatchMock* watchMock;
      PreamblePrinterSelfMocked()
      {
         _console.reset(consoleMock = new ConsoleMock);
         _watch.reset(watchMock = new WatchMock);
      }
      ZENMOCK_NONVOID1_CONST(string, MakeThirdLinePrefix, size_t)
      ZENMOCK_NONVOID2_CONST(string, MakeThirdLineSuffix, bool, unsigned)
   } _preamblePrinterSelfMocked;

   PreamblePrinter _preamblePrinter;
   const MachineNameGetterMock* _machineNameGetterMock = nullptr;

   STARTUP
   {
      _preamblePrinter._machineNameGetter.reset(_machineNameGetterMock = new MachineNameGetterMock);
   }

      TEST(Constructor_NewsConsoleAndWatch)
   {
      PreamblePrinter preamblePrinter;
      POINTER_WAS_NEWED(preamblePrinter._console);
      POINTER_WAS_NEWED(preamblePrinter._watch);
      POINTER_WAS_NEWED(preamblePrinter._machineNameGetter);
   }

   TEST(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
   {
      _preamblePrinterSelfMocked.consoleMock->WriteColorMock.Expect();
      _preamblePrinterSelfMocked.consoleMock->WriteLineMock.Expect();
      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();
      const string dateTimeNowWithTimeZone = _preamblePrinterSelfMocked.watchMock->DateTimeNowWithTimeZoneMock.ReturnRandom();
      const string thirdLinePrefix = _preamblePrinterSelfMocked.MakeThirdLinePrefixMock.ReturnRandom();
      const string thirdLineSuffix = _preamblePrinterSelfMocked.MakeThirdLineSuffixMock.ReturnRandom();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      zenUnitArgs.random = Random<bool>();
      zenUnitArgs.randomseed = Random<unsigned>();
      //
      _preamblePrinterSelfMocked.PrintOpeningThreeLines(zenUnitArgs, &testClassRunnerRunnerMock);
      //
      ZEN(_preamblePrinterSelfMocked.watchMock->DateTimeNowWithTimeZoneMock.CalledOnce());
      ZEN(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteColorMock.CalledNTimesWith(3, "[ZenUnit]", Color::Green));
      ZEN(_preamblePrinterSelfMocked.MakeThirdLinePrefixMock.CalledOnceWith(numberOfTestClassesToBeRun));
      ZEN(_preamblePrinterSelfMocked.MakeThirdLineSuffixMock.
         CalledOnceWith(zenUnitArgs.random, zenUnitArgs.randomseed));
      const string expectedThirdLineAndLineBreak = thirdLinePrefix + thirdLineSuffix + "\n";
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteLineMock.CalledAsFollows(
      {
         " Running " + zenUnitArgs.commandLine,
         " Running at " + dateTimeNowWithTimeZone,
         expectedThirdLineAndLineBreak
      }));
   }

   TEST2X2(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName,
      const string& expectedReturnValuePrefix, size_t numberOfTestClasses,
      " Running 0 test classes on machine ", size_t(0),
      " Running 1 test class on machine ", size_t(1),
      " Running 2 test classes on machine ", size_t(2))
   {
      const string machineName = _machineNameGetterMock->GetMachineNameMock.ReturnRandom();
      //
      const string thirdLinePrefix = _preamblePrinter.MakeThirdLinePrefix(numberOfTestClasses);
      //
      ZEN(_machineNameGetterMock->GetMachineNameMock.CalledOnce());
      const string expectedReturnValue = expectedReturnValuePrefix + machineName;
      ARE_EQUAL(expectedReturnValue, thirdLinePrefix);
   }

   TEST3X3(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString,
      const string& expectedReturnValue, bool random, unsigned randomseed,
      "", false, NA<unsigned>(),
      " (random seed 0)", true, 0u,
      " (random seed 1)", true, 1u)
   {
      const string thirdLineSuffix = _preamblePrinter.MakeThirdLineSuffix(random, randomseed);
      ARE_EQUAL(expectedReturnValue, thirdLineSuffix);
   }

   RUN_TESTS(PreamblePrinterTests)
}

