#include "pch.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#ifdef __linux__
#include <strings.h>
#endif

namespace ZenUnit
{
   bool operator<(
      const std::unique_ptr<TestClassRunner>& leftTestClassRunner,
      const std::unique_ptr<TestClassRunner>& rightTestClassRunner)
   {
      const char* leftTestClassName = leftTestClassRunner->TestClassName();
      const char* rightTestClassName = rightTestClassRunner->TestClassName();
      int caseInsensitiveComparisonResult = 0;
#ifdef __linux__
      caseInsensitiveComparisonResult = strcasecmp(leftTestClassName, rightTestClassName);
#elif _WIN32
      caseInsensitiveComparisonResult = _strcmpi(leftTestClassName, rightTestClassName);
#endif
      const bool isLessThan = caseInsensitiveComparisonResult < 0;
      return isLessThan;
   }
}
