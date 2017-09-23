#include "pch.h"
#include "ZenUnit/TestRunners/RunTests.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   int RunTests(int argc, char* argv[])
   {
      TestRunner& testRunner = TestRunner::Instance();
      const std::vector<std::string> args = Vector::FromArgcArgv(argc, argv);
      const int exitCode = testRunner.ParseArgsRunTestsPrintResults(args);
      return exitCode;
   }
}
