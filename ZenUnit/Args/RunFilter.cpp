//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Args/RunFilter.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   INLINE RunFilter::RunFilter()
      : testCaseNumber(0)
   {
   }

   INLINE RunFilter::RunFilter(const std::string& testClassName, const std::string& testName, unsigned testCaseNumber)
      : testClassName(testClassName)
      , testName(testName)
      , testCaseNumber(testCaseNumber)
   {
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::RunFilter>::AssertEqual(
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
   INLINE RunFilter Random<RunFilter>()
   {
      RunFilter randomRunFilter;
      randomRunFilter.testClassName = ZenUnit::Random<std::string>();
      randomRunFilter.testName = ZenUnit::Random<std::string>();
      randomRunFilter.testCaseNumber = ZenUnit::Random<unsigned>();
      return randomRunFilter;
   }
}