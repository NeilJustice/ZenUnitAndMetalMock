#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Utils/Set.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Vector.h"
#include <vector>

namespace ZenUnit
{
   ArgsParser::ArgsParser()
      : _console(new Console)
      , _watch(new Watch)
      , _String_ToUnsigned(String::ToUnsigned)
   {
   }

   ZenUnitArgs ArgsParser::Parse(const std::vector<std::string>& args) const
   {
      if (args.size() > 8)
      {
         _console->WriteLine("ZenUnit argument error: Too many arguments.\n");
         _console->WriteLineAndExit(Usage(), 1);
      }
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Vector::Join(args, ' ');
      const size_t numberOfArgs = args.size();
      for (size_t argIndex = 1; argIndex < numberOfArgs; ++argIndex)
      {
         const std::string& arg = args[argIndex];
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
            _console->WriteLineAndExit(Usage(), 0);
         }
         else if (!String::Contains(arg, "="))
         {
            _console->WriteLine("ZenUnit argument error: Invalid argument \"" + arg + "\"\n");
            _console->WriteLineAndExit(Usage(), 1);
         }
         else
         {
            const std::vector<std::string> splitArg = String::Split(arg, '=');
            if (splitArg.size() != 2)
            {
               _console->WriteLine("ZenUnit argument error: Malformed -name=value argument: " + arg + "\n");
               _console->WriteLineAndExit(Usage(), 1);
            }
            try
            {
               const std::string& argName = splitArg[0];
               const std::string& argValueString = splitArg[1];
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
                  throw std::invalid_argument("");
               }
            }
            catch (const std::invalid_argument&)
            {
               _console->WriteLine("ZenUnit argument error: Malformed -name=value argument: " + arg + "\n");
               _console->WriteLineAndExit(Usage(), 1);
            }
         }
      }
      return zenUnitArgs;
   }

   const std::string& ArgsParser::Usage()
   {
      static const std::string usage = R"(ZenUnit v0.1.0
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
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.)";
      return usage;
   }
}
