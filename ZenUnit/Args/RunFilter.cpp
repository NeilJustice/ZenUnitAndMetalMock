#include "pch.h"
#include "ZenUnit/Args/RunFilter.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

void ZenUnitEqualizer<ZenUnit::RunFilter>::AssertEqual(
   const ZenUnit::RunFilter& expectedRunFilter,
   const ZenUnit::RunFilter& actualRunFilter)
{
   ARE_EQUAL(expectedRunFilter.testClassName, actualRunFilter.testClassName);
   ARE_EQUAL(expectedRunFilter.testName, actualRunFilter.testName);
   ARE_EQUAL(expectedRunFilter.testCaseNumber, actualRunFilter.testCaseNumber);
}

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