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
         if (arg == "-exit0")
         {
            zenUnitArgs.exit0 = true;
         }
         else if (arg == "-noskips")
         {
            zenUnitArgs.noskips = true;
         }
         else if (arg == "-help" || arg == "--help")
         {
            _console->WriteLineAndExit(Usage, 0);
         }
         else if (!String::Contains(arg, "="))
         {
            _console->WriteLine("ZenUnit argument error: Invalid argument \"" + arg + "\"");
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
               zenUnitArgs.times = value;
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

const string ArgsParser::Usage = R"(C++ unit testing framework ZenUnit and C++ mocking framework ZenMock
Version 0.1.1
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests.
-times=<N>
   Run all non-skipped tests N times.
   Useful for ensuring tests still pass when run a second time
   and for increasing test run duration to allow for data-dense
   performance profiling of ZenUnit and test code.
-exit0
   Always exit 0 regardless of test run outcome.
   This option is useful for always allowing the launch of a debugger
   or non-debugging console window after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This option is useful for continuous integration servers
   to defend against the possibility of a quality-compromising
   culture of complacency developing around committed skipped tests.
-help or --help
   Display this help.)";
}
