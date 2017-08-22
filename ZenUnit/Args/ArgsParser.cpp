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
         if (arg == "-minimalist")
         {
            zenUnitArgs.printMode = PrintMode::Minimalist;
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
            zenUnitArgs.randomseed = _watch->SecondsSince1970CastToUnsignedShort();
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
               const string& argName = splitArg[0];
               const string& argValueString = splitArg[1];
               unsigned argValue = 0;
               if (argName == "-testruns")
               {
                  argValue = _String_ToUnsigned(argValueString);
                  zenUnitArgs.testruns = argValue;
               }
               else if (argName == "-random")
               {
                  zenUnitArgs.random = true;
                  argValue = _String_ToUnsigned(argValueString);
                  zenUnitArgs.randomseed = static_cast<unsigned short>(argValue);
                  zenUnitArgs.randomseedsetbyuser = true;
               }
               else
               {
                  throw invalid_argument("");
               }
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

const string ArgsParser::Usage = R"(ZenUnit and ZenMock v0.1.0
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimalist
   Print only preamble and conclusion.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for not blocking the launch of a debugger.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Powerful option for continuous integration servers to guard against
   the possibility of a quality-compromising culture of complacency
   developing around skipped tests. "Skip it and ship it!"
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Powerful option for maximizing testing rigor.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Powerful option for maximizing testing rigor.)";
}
