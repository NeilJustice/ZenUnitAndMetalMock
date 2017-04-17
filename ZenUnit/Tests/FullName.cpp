#include "pch.h"
#include "FullName.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   FullName::FullName()
      : testClassName(nullptr)
      , testName(nullptr)
   {
   }

   FullName::FullName(const char* testClassName, const char* testName)
      : testClassName(testClassName)
      , testName(testName)
   {
   }

   string FullName::TestsAndTestLines() const
   {
      string testsAndTestLines = String::Concat("TESTS(", testClassName, ")\nTEST(", testName, ")");
      return testsAndTestLines;
   }
}

void ZenUnitEqualizer<ZenUnit::FullName>::
AssertEqual(
   const ZenUnit::FullName& expectedFullName,
   const ZenUnit::FullName& actualFullName)
{
   ARE_EQUAL(expectedFullName.testClassName, actualFullName.testClassName);
   ARE_EQUAL(expectedFullName.testName, actualFullName.testName);
}
