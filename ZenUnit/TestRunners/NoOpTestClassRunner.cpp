#include "pch.h"
#include "NoOpTestClassRunner.h"

namespace ZenUnit
{
   inline const char* NoOpTestClassRunner::TestClassName() const
   {
      return "FilteredOut";
   }

   inline size_t NoOpTestClassRunner::NumberOfTestCases() const
   {
      return 0;
   }

   inline TestClassResult NoOpTestClassRunner::RunTests()
   {
      return TestClassResult();
   }

   inline bool NoOpTestClassRunner::HasTestNameThatCaseInsensitiveMatchesPattern(const std::string& testNamePattern) const
   {
      return false;
   }
}
