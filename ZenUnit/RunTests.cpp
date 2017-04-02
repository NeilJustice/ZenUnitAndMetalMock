#include "pch.h"
#include "RunTests.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   int RunTests(int argc, const char* argv[])
   {
      TestRunner& testRunner = TestRunner::Instance();
      const vector<string> args = Vector::FromArgcArgv(argc, argv);
      const int exitCode = testRunner.ParseArgsRunTestsPrintResults(args);
      return exitCode;
   }
}
