#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/TestRunners/Mock/TestClassRunnerRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Mock/DebugOrReleaseModeGetterMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Mock/MachineNameGetterMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   AFACT(Constructor_NewsConsoleAndWatch)
   AFACT(PrintPreambleAndGetStartTime_PrintsCommandLineAndStartTimeAndTestAndTestClassCounts_ReturnsStartTime)
   FACTS(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName)
   FACTS(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString)
   EVIDENCE

   class PreamblePrinterSelfMocked : public Zen::Mock<PreamblePrinter>
   {
   public:
      const ConsoleMock* consoleMock = nullptr;
      const DebugOrReleaseGetterMock* debugOrReleaseGetterMock = nullptr;
      const WatchMock* watchMock = nullptr;
      PreamblePrinterSelfMocked() noexcept
      {
         _console.reset(consoleMock = new ConsoleMock);
         _debugOrReleaseGetter.reset(debugOrReleaseGetterMock = new DebugOrReleaseGetterMock);
         _watch.reset(watchMock = new WatchMock);
      }
      ZENMOCK_NONVOID1_CONST(string, MakeThirdLinePrefix, size_t)
      ZENMOCK_NONVOID2_CONST(string, MakeThirdLineSuffix, bool, unsigned short)
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
      POINTER_WAS_NEWED(preamblePrinter._debugOrReleaseGetter);
      POINTER_WAS_NEWED(preamblePrinter._watch);
      POINTER_WAS_NEWED(preamblePrinter._machineNameGetter);
   }

   TEST(PrintPreambleAndGetStartTime_PrintsCommandLineAndStartTimeAndTestAndTestClassCounts_ReturnsStartTime)
   {
      _preamblePrinterSelfMocked.consoleMock->WriteColorMock.Expect();
      const string runningInDebugOrReleaseModeString = _preamblePrinterSelfMocked.
         debugOrReleaseGetterMock->GetRunningInDebugOrReleaseModeStringMock.ReturnRandom();
      _preamblePrinterSelfMocked.consoleMock->WriteLineMock.Expect();
      TestClassRunnerRunnerMock testClassRunnerRunnerMock;
      const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();
      const string startTime = _preamblePrinterSelfMocked.watchMock->DateTimeNowMock.ReturnRandom();
      const string thirdLinePrefix = _preamblePrinterSelfMocked.MakeThirdLinePrefixMock.ReturnRandom();
      const string thirdLineSuffix = _preamblePrinterSelfMocked.MakeThirdLineSuffixMock.ReturnRandom();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      zenUnitArgs.random = Random<bool>();
      zenUnitArgs.randomseed = Random<unsigned short>();
      //
      const string returnedStartTime = _preamblePrinterSelfMocked.
         PrintPreambleAndGetStartTime(zenUnitArgs, &testClassRunnerRunnerMock);
      //
      ZEN(_preamblePrinterSelfMocked.watchMock->DateTimeNowMock.CalledOnce());
      ZEN(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteColorMock.CalledNTimesWith(3, "[ZenUnit]", Color::Green));
      ZEN(_preamblePrinterSelfMocked.debugOrReleaseGetterMock->GetRunningInDebugOrReleaseModeStringMock.CalledOnce());
      ZEN(_preamblePrinterSelfMocked.MakeThirdLinePrefixMock.CalledOnceWith(numberOfTestClassesToBeRun));
      ZEN(_preamblePrinterSelfMocked.MakeThirdLineSuffixMock.CalledOnceWith(zenUnitArgs.random, zenUnitArgs.randomseed));
      const string expectedThirdLineAndLineBreak = thirdLinePrefix + thirdLineSuffix + "\n";
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteLineMock.CalledAsFollows(
      {
         { runningInDebugOrReleaseModeString + zenUnitArgs.commandLine },
         { " Running at " + startTime },
         { expectedThirdLineAndLineBreak }
      }));
      ARE_EQUAL(startTime, returnedStartTime);
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
      const string expectedReturnValue = expectedReturnValuePrefix + machineName + " with ZenUnit version 0.4.0";
      ARE_EQUAL(expectedReturnValue, thirdLinePrefix);
   }

   TEST3X3(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString,
      const string& expectedReturnValue, bool random, unsigned short randomseed,
      "", false, ZenUnit::Random<unsigned short>(),
      " (random seed 0)", true, static_cast<unsigned short>(0),
      " (random seed 1)", true, static_cast<unsigned short>(1))
   {
      const string thirdLineSuffix = _preamblePrinter.MakeThirdLineSuffix(random, randomseed);
      ARE_EQUAL(expectedReturnValue, thirdLineSuffix);
   }

   RUN_TESTS(PreamblePrinterTests)
}
