#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/TestRunners/MachineNameGetter.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Time/Watch.h"

namespace ZenUnit
{
   PreamblePrinter::PreamblePrinter()
      : _console(new Console)
      , _watch(new Watch)
      , _machineNameGetter(new MachineNameGetter)
   {
   }

   PreamblePrinter::~PreamblePrinter() = default;

   void PreamblePrinter::PrintOpeningThreeLines(
      const string& commandLine, const MultiTestClassRunner* multiTestClassRunner) const
   {
      _console->WriteColor("[ZenUnit]", Color::Green);
      _console->WriteLine(" Running " + commandLine);
      _console->WriteColor("[ZenUnit]", Color::Green);
      const string timeZoneDateTimeNow = _watch->TimeZoneDateTimeNow();
      _console->WriteLine(" Running at " + timeZoneDateTimeNow);
      _console->WriteColor("[ZenUnit]", Color::Green);
      const size_t numberOfTestClasses = multiTestClassRunner->NumberOfTestClasses();
      const bool testClassesPlural = numberOfTestClasses > 1 || numberOfTestClasses == 0;
      const string machineName = _machineNameGetter->GetMachineName();
      const string runningTestClassesLine = String::Concat(
         " Running ", numberOfTestClasses, " test ", (testClassesPlural ? "classes" : "class"),
         " on machine ", machineName);
      _console->WriteLine(runningTestClassesLine);
      if (numberOfTestClasses > 0)
      {
         _console->WriteNewline();
      }
   }
}
