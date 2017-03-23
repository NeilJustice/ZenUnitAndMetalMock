#include "pch.h"
#include "PreamblePrinter.h"
#include "TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Utils/Time/Watch.h"
#include "ZenUnit/TestRunners/MachineNameGetter.h"

namespace ZenUnit
{
   PreamblePrinter::PreamblePrinter()
      : _console(new Console)
      , _watch(new Watch)
      , _machineNameGetter(new MachineNameGetter)
   {
   }

   PreamblePrinter::~PreamblePrinter()
   {
   }

   void PreamblePrinter::PrintOpeningThreeLines(
      const MultiTestClassRunner* multiTestClassRunner, const string& commandLine) const
   {
      _console->WriteColor("[ZenUnit]", Color::Green);
      _console->WriteLine(" Running " + commandLine);
      _console->WriteColor("[ZenUnit]", Color::Green);
      string timeZoneDateTimeNow = _watch->TimeZoneDateTimeNow();
      _console->WriteLine(" Running at " + timeZoneDateTimeNow);
      _console->WriteColor("[ZenUnit]", Color::Green);
      size_t numberOfTestClasses = multiTestClassRunner->NumberOfTestClasses();
      bool testClassesPlural = numberOfTestClasses > 1 || numberOfTestClasses == 0;
      string machineName = _machineNameGetter->GetMachineName();
      string runningTestClassesLine = String::Concat(
         " Running ", numberOfTestClasses, " test ", (testClassesPlural ? "classes" : "class"),
         " on machine ", machineName);
      _console->WriteLine(runningTestClassesLine);
      if (numberOfTestClasses > 0)
      {
         _console->WriteNewline();
      }
   }
}
