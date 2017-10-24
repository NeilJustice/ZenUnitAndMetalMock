#include "pch.h"
#include "NoOpTestClassRunner.h"

namespace ZenUnit
{
   const char* NoOpTestClassRunner::TestClassName() const
   {
      return "FilteredOut";
   }

   size_t NoOpTestClassRunner::NumberOfTestCases() const
   {
      return 0;
   }

   TestClassResult NoOpTestClassRunner::RunTests()
   {
      return TestClassResult();
   }

   bool NoOpTestClassRunner::HasTestNameThatCaseInsensitiveMatchesPattern(const std::string& testNamePattern) const
   {
      return false;
   }
}
