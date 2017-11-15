//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/TestRunners/MachineNameGetter.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Time/Watch.h"

namespace ZenUnit
{
   INLINE PreamblePrinter::PreamblePrinter()
      : _console(new Console)
      , _watch(new Watch)
      , _machineNameGetter(new MachineNameGetter)
   {
   }

   INLINE PreamblePrinter::~PreamblePrinter() = default;

   INLINE void PreamblePrinter::PrintOpeningThreeLines(
      const ZenUnitArgs& zenUnitArgs,
      const MultiTestClassRunner* multiTestClassRunner) const
   {
      _console->WriteColor("[ZenUnit]", Color::Green);
      _console->WriteLine(" Running " + zenUnitArgs.commandLine);
      _console->WriteColor("[ZenUnit]", Color::Green);
      const std::string timeZoneDateTimeNow = _watch->TimeZoneDateTimeNow();
      _console->WriteLine(" Running at " + timeZoneDateTimeNow);
      _console->WriteColor("[ZenUnit]", Color::Green);
      const size_t numberOfTestClassesToBeRun = multiTestClassRunner->NumberOfTestClassesToBeRun();
      const std::string thirdLinePrefix = MakeThirdLinePrefix(numberOfTestClassesToBeRun);
      const std::string thirdLineSuffix = MakeThirdLineSuffix(zenUnitArgs.random, zenUnitArgs.randomseed);
      const std::string thirdLine = thirdLinePrefix + thirdLineSuffix;
      _console->WriteLine(thirdLine);
      _console->WriteNewLine();
   }

   INLINE std::string PreamblePrinter::MakeThirdLinePrefix(size_t numberOfTestClassesToBeRun) const
   {
      const bool testClassesPlural = numberOfTestClassesToBeRun > 1 || numberOfTestClassesToBeRun == 0;
      const std::string machineName = _machineNameGetter->GetMachineName();
      const std::string thirdLinePrefix = String::Concat(
         " Running ", numberOfTestClassesToBeRun, " test ", testClassesPlural ? "classes" : "class",
         " on machine ", machineName);
      return thirdLinePrefix;
   }

   INLINE std::string PreamblePrinter::MakeThirdLineSuffix(bool random, unsigned short randomseed) const
   {
      const std::string thirdLineSuffix = random ? " with random seed " + std::to_string(randomseed) : "";
      return thirdLineSuffix;
   }
}
