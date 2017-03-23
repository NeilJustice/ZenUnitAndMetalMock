#include "pch.h"
#include "ArgsParser.h"
#include "Console/Console.h"
#include "Utils/Vector.h"
#include "Utils/Set.h"

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
      size_t numberOfArgs = args.size();
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

const string ArgsParser::Usage = R"(ZenUnit and ZenMock
Usage: ./<TestsBinaryName> [Options]

Options:

None
   Run all non-skipped tests
-exit0
   Always exit 0 regardless of test run outcome.
   This setting is useful for not preventing the launch of a debugger
   after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This setting is useful for continuous integration servers
   to ensure a culture of complacency with respect to committed
   skipped tests being OK is programatically prevented from taking hold.
-help or --help
   Display this message)";
}
