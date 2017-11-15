#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/TestRunners/RunTests.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   INLINE int RunTests(int argc, char* argv[])
   {
      const std::vector<std::string> args = Vector::FromArgcArgv(argc, argv);
      TestRunner& zenUnitTestRunner = TestRunner::Instance();
      const int exitCode = zenUnitTestRunner.ParseArgsRunTestClassesPrintResults(args);
      return exitCode;
   }
}
