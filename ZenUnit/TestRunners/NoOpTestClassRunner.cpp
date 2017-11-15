#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "NoOpTestClassRunner.h"

namespace ZenUnit
{
   INLINE const char* NoOpTestClassRunner::TestClassName() const
   {
      return "FilteredOut";
   }

   INLINE size_t NoOpTestClassRunner::NumberOfTestCases() const
   {
      return 0;
   }

   INLINE TestClassResult NoOpTestClassRunner::RunTests()
   {
      return TestClassResult();
   }

   INLINE bool NoOpTestClassRunner::HasTestNameThatCaseInsensitiveMatchesPattern(const std::string&) const
   {
      return false;
   }
}
