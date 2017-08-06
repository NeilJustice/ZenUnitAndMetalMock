#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Utils/Set.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   ArgsParser::ArgsParser()
      : _console(new Console)
      , _watch(new Watch)
      , _String_ToUnsigned(String::ToUnsigned)
   {
   }

   ZenUnitArgs ArgsParser::Parse(const vector<string>& args) const
   {
      const size_t ExeArgSize = 1;
      if (args.size() > ExeArgSize + ZenUnitArgs::NumberOfValidArgs)
      {
         _console->WriteLine("ZenUnit argument error: Too many arguments.\n");
         _console->WriteLineAndExit(Usage, 1);
      }
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Vector::Join(args, ' ');
      const size_t numberOfArgs = args.size();
      for (size_t argIndex = 1; argIndex < numberOfArgs; ++argIndex)
      {
         const string& arg = args[argIndex];
         if (arg == "-minimal")
         {
            zenUnitArgs.printMode = PrintMode::Minimal;
         }
         else if (arg == "-detailed")
         {
            zenUnitArgs.printMode = PrintMode::Detailed;
         }
         else if (arg == "-exit0")
         {
            zenUnitArgs.exit0 = true;
         }
         else if (arg == "-failskips")
         {
            zenUnitArgs.failskips = true;
         }
         else if (arg == "-random")
         {
            zenUnitArgs.random = true;
            zenUnitArgs.randomseed = _watch->SecondsSince1970CastToAnUnsignedShort();
         }
         else if (arg == "-help" || arg == "--help")
         {
            _console->WriteLineAndExit(Usage, 0);
         }
         else if (!String::Contains(arg, "="))
         {
            _console->WriteLine("ZenUnit argument error: Invalid argument \"" + arg + "\"\n");
            _console->WriteLineAndExit(Usage, 1);
         }
         else
         {
            const vector<string> splitArg = String::Split(arg, '=');
            if (splitArg.size() != 2)
            {
               _console->WriteLine("ZenUnit argument error: Malformed -name=value argument: " + arg + "\n");
               _console->WriteLineAndExit(Usage, 1);
            }
            try
            {
               const string& valueString = splitArg[1];
               const unsigned value = _String_ToUnsigned(valueString);
               zenUnitArgs.testruns = value;
            }
            catch (const invalid_argument&)
            {
               _console->WriteLine("ZenUnit argument error: Malformed -name=value argument: " + arg + "\n");
               _console->WriteLineAndExit(Usage, 1);
            }
         }
      }
      return zenUnitArgs;
   }

const string ArgsParser::Usage = R"(ZenUnit and ZenMock
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimal
   Print only preamble and conclusion instead of detailed information.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful for always allowing the Visual Studio debugger to launch.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Useful option for continuous integration servers to guard against
   quality-compromising complacency with respect to skipped tests.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Key option for maximizing testing rigor.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Key option for maximizing testing rigor.
-help or --help
   Display this help.)";
}
