#include "pch.h"
#include "RunTests.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   int RunTests(int argc, char* argv[])
   {
      TestRunner& testRunner = TestRunner::Instance();
      vector<string> args = Vector::FromArgcArgv(argc, argv);
      int exitCode = testRunner.ParseArgsRunTestsPrintResults(args);
      return exitCode;
   }
}
