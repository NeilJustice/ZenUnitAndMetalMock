#include "pch.h"
#include "Args/ArgsParser.h"
#include "Console/Console.h"
#include "Utils/Set.h"
#include "Utils/Vector.h"

namespace ZenUnit
{
   ArgsParser::ArgsParser()
      : _console(new Console)
   {
   }

   ZenUnitArgs ArgsParser::Parse(const vector<string>& args) const
   {
      constexpr size_t ExeArgSize = 1;
      if (args.size() > ExeArgSize + ZenUnitArgs::ValidArgs.size())
      {
         _console->WriteLine("ZenUnit argument error: Too many arguments");
         _console->WriteLineAndExit(Usage, 2);
      }
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Vector::Join(args, ' ');
      const size_t numberOfArgs = args.size();
      for (size_t argIndex = 1; argIndex < numberOfArgs; ++argIndex)
      {
         const string& arg = args[argIndex];
         if (!Set::Contains(ZenUnitArgs::ValidArgs, arg))
         {
            _console->WriteLine("ZenUnit argument error: Invalid argument \"" + arg + "\"");
            _console->WriteLineAndExit(Usage, 2);
         }
         if (arg == "-help" || arg == "--help")
         {
            _console->WriteLineAndExit(Usage, 0);
         }
         else if (arg == "-exit0")
         {
            zenUnitArgs.exit0 = true;
         }
         else if (arg == "-noskips")
         {
            zenUnitArgs.noskips = true;
         }
      }
      return zenUnitArgs;
   }

const string ArgsParser::Usage = R"(C++ unit testing framework ZenUnit and C++ mocking framework ZenMock
Version 0.1.1 2017-02-14

Usage: ./<TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests.
-exit0
   Always exit 0 regardless of test run outcome.
   This option is useful for always allowing the launch of a debugger
   or non-debugging console window after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This option is useful for continuous integration servers
   to defend against the possibility of a quality-compromising
   culture of complacency developing around committed skipped tests.)";
}
