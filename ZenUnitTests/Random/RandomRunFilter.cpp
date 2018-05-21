#include "pch.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

namespace ZenUnit
{
   template<>
   RunFilter Random<RunFilter>()
   {
      RunFilter randomRunFilter;
      randomRunFilter.testClassNamePattern = ZenUnit::Random<std::string>();
      randomRunFilter.testNamePattern = ZenUnit::Random<std::string>();
      randomRunFilter.testCaseNumber = ZenUnit::Random<unsigned>();
      return randomRunFilter;
   }
}
