#include "pch.h"
#include "TestClassRunner.h"
#ifdef __linux__
#include <strings.h>
#endif

namespace ZenUnit
{
   bool operator<(
      const unique_ptr<TestClassRunner>& leftTestClassRunner,
      const unique_ptr<TestClassRunner>& rightTestClassRunner)
   {
      const char* leftTestClassName = leftTestClassRunner->TestClassNameForSorting();
      const char* rightTestClassName = rightTestClassRunner->TestClassNameForSorting();
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
