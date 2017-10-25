#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Utils/Set.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Vector.h"
#include <vector>

namespace ZenUnit
{
   ArgsParser::ArgsParser()
      : _console(new Console)
      , _runFilterParser(new RunFilterParser)
      , call_String_ToUnsigned(String::ToUnsigned)
   {
   }

   ArgsParser::~ArgsParser() = default;

   ZenUnitArgs ArgsParser::Parse(const std::vector<std::string>& args) const
   {
      if (args.size() > 9)
      {
         _console->WriteLine("ZenUnit argument error. Too many arguments.\n");
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
         else if (arg == "-pause")
         {
            zenUnitArgs.pause = true;
         }
         else if (arg == "-wait")
         {
            zenUnitArgs.wait = true;
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
         }
         else if (arg == "-help" || arg == "--help")
         {
            _console->WriteLineAndExit(Usage(), 0);
         }
         else if (!String::Contains(arg, "="))
         {
            WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid argument \"" + arg + "\"");
         }
         else
         {
            const std::vector<std::string> splitArg = String::Split(arg, '=');
            if (splitArg.size() != 2)
            {
               WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid -name=value argument value: " + arg);
            }
            try
            {
               const std::string& argName = splitArg[0];
               const std::string& argValueString = splitArg[1];
               unsigned argValue = 0;
               if (argName == "-run")
               {
                  const std::vector<std::string> runFilterStrings = String::Split(argValueString, ',');
                  zenUnitArgs.runFilters = _runFilterParser->Parse(runFilterStrings);
               }
               else if (argName == "-testruns")
               {
                  argValue = call_String_ToUnsigned(argValueString);
                  zenUnitArgs.testruns = argValue;
               }
               else if (argName == "-random")
               {
                  zenUnitArgs.random = true;
                  argValue = call_String_ToUnsigned(argValueString);
                  zenUnitArgs.randomseed = static_cast<unsigned short>(argValue);
                  zenUnitArgs.randomseedsetbyuser = true;
               }
               else
               {
                  WriteZenUnitArgumentErrorAndUsageThenExit1("Unrecognized -name=value argument: " + arg);
               }
            }
            catch (const std::invalid_argument&)
            {
               WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid -name=value argument value: " + arg);
            }
         }
      }
      return zenUnitArgs;
   }

   void ArgsParser::WriteZenUnitArgumentErrorAndUsageThenExit1(const std::string& errorMessage) const
   {
      _console->WriteLine("ZenUnit argument error. " + errorMessage + "\n");
      _console->WriteLineAndExit(Usage(), 1);
   }

   const std::string& ArgsParser::Usage()
   {
      static const std::string usage = R"(ZenUnit v0.1.0
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimalist
   Print only preamble, any test failure details, and conclusion.
-run=<TestClassName[.TestName],TestClassName[.TestName]...>
   Run only specified case-insensitive test classes and/or tests.
-pause
   Wait for input before running tests to allow attaching a profiler or debugger.
-wait
   Wait for input before closing console window.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for never blocking the launch of the Visual Studio debugger
   when running ZenUnit tests as a post-build event.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Useful option for continuous integration servers to reduce
   the probability of a quality-compromising culture of complacency
   developing around skipped tests.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Useful option for increasing testing rigor.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Useful option for increasing testing rigor, especially when used with -random.)";
      return usage;
   }
}
