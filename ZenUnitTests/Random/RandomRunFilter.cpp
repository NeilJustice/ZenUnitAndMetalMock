#include "pch.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

namespace ZenUnit
{
   template<>
   RunFilter Random<RunFilter>()
   {
      RunFilter randomRunFilter;
      randomRunFilter.testClassName = ZenUnit::Random<std::string>();
      randomRunFilter.testName = ZenUnit::Random<std::string>();
      randomRunFilter.testCaseNumber = ZenUnit::Random<unsigned>();
      return randomRunFilter;
   }
}
