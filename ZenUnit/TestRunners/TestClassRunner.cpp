#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/Utils/StringUtil.h"
#ifdef __linux__
#include <strings.h>
#endif

namespace ZenUnit
{
   INLINE bool operator<(
      const std::unique_ptr<TestClassRunner>& leftTestClassRunner,
      const std::unique_ptr<TestClassRunner>& rightTestClassRunner)
   {
      const char* leftTestClassName = leftTestClassRunner->TestClassName();
      const char* rightTestClassName = rightTestClassRunner->TestClassName();
      int caseInsensitiveComparisonResult = String::IgnoreCaseStrcmp(leftTestClassName, rightTestClassName);
      const bool isLessThan = caseInsensitiveComparisonResult < 0;
      return isLessThan;
   }
}
