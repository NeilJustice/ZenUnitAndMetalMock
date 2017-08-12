#include "pch.h"
#include "Console/Mock/ConsoleMock.h"
#include "TestRunners/Mock/TestClassMultiRunnerMock.h"
#include "Utils/Mock/MachineNameGetterMock.h"
#include "Utils/Time/Mock/WatchMock.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "ZenUnit/Utils/Random.h"

namespace ZenUnit
{
   TESTS(PreamblePrinterTests)
   FACT(Constructor_NewsConsoleAndWatch)
   FACT(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
   FACTS(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName)
   FACTS(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString)
   BEGINPROOF

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
      ZENMOCK_NONVOID2_CONST(string, MakeThirdLineSuffix, bool, unsigned short)
   } _preamblePrinterSelfMocked;

   PreamblePrinter _preamblePrinter;
   const MachineNameGetterMock* _machineNameGetterMock;

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
      _preamblePrinterSelfMocked.consoleMock->WriteNewLineMock.Expect();
      TestClassMultiRunnerMock multiTestClassRunnerMock;
      const size_t NumberOfTestClasses = Random<size_t>();
      multiTestClassRunnerMock.NumberOfTestClassesMock.ExpectAndReturn(NumberOfTestClasses);

      const string TimeZoneDateTimeNow = Random<string>();
      _preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.ExpectAndReturn(TimeZoneDateTimeNow);

      const string ThirdLinePrefix = Random<string>();
      _preamblePrinterSelfMocked.MakeThirdLinePrefixMock.ExpectAndReturn(ThirdLinePrefix);
      const string ThirdLineSuffix = Random<string>();
      _preamblePrinterSelfMocked.MakeThirdLineSuffixMock.ExpectAndReturn(ThirdLineSuffix);

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      zenUnitArgs.random = Random<bool>();
      zenUnitArgs.randomseed = Random<unsigned short>();
      //
      _preamblePrinterSelfMocked.PrintOpeningThreeLines(zenUnitArgs, &multiTestClassRunnerMock);
      //
      ZEN(_preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.AssertCalledOnce());
      ZEN(multiTestClassRunnerMock.NumberOfTestClassesMock.AssertCalledOnce());
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteColorMock.
          AssertCalledNTimesWith(3, "[ZenUnit]", Color::Green));
      ZEN(_preamblePrinterSelfMocked.MakeThirdLinePrefixMock.AssertCalledOnceWith(NumberOfTestClasses));
      ZEN(_preamblePrinterSelfMocked.MakeThirdLineSuffixMock.
         AssertCalledOnceWith(zenUnitArgs.random, zenUnitArgs.randomseed));
      const string ExpectedThirdLine = ThirdLinePrefix + ThirdLineSuffix;
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteLineMock.AssertCalls(
      {
         " Running " + zenUnitArgs.commandLine,
         " Running at " + TimeZoneDateTimeNow,
         ExpectedThirdLine
      }));
      ZEN(_preamblePrinterSelfMocked.consoleMock->WriteNewLineMock.AssertCalledOnce());
   }

   TEST2X2(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName,
      const string& expectedReturnValuePrefix, size_t numberOfTestClasses,
      " Running 0 test classes on machine ", size_t(0),
      " Running 1 test class on machine ", size_t(1),
      " Running 2 test classes on machine ", size_t(2))
   {
      const string MachineName = Random<string>();
      _machineNameGetterMock->GetMachineNameMock.ExpectAndReturn(MachineName);
      //
      const string thirdLinePrefix = _preamblePrinter.MakeThirdLinePrefix(numberOfTestClasses);
      //
      ZEN(_machineNameGetterMock->GetMachineNameMock.AssertCalledOnce());
      const string expectedReturnValue = expectedReturnValuePrefix + MachineName;
      ARE_EQUAL(expectedReturnValue, thirdLinePrefix);
   }

   TEST3X3(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString,
      const string& expectedReturnValue, bool random, unsigned short randomseed,
      "", false, NA<unsigned short>(),
      " with random seed 0", true, unsigned short(0),
      " with random seed 1", true, unsigned short(1))
   {
      const string thirdLineSuffix = _preamblePrinter.MakeThirdLineSuffix(random, randomseed);
      ARE_EQUAL(expectedReturnValue, thirdLineSuffix);
   }

   }; RUN(PreamblePrinterTests)
}
