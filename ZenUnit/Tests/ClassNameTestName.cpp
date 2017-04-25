#include "pch.h"
#include "ClassNameTestName.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   ClassNameTestName::ClassNameTestName()
      : testClassName(nullptr)
      , testName(nullptr)
   {
   }

   ClassNameTestName::ClassNameTestName(const char* testClassName, const char* testName)
      : testClassName(testClassName)
      , testName(testName)
   {
   }

   string ClassNameTestName::TestsAndTestLines() const
   {
      string testsAndTestLines = String::Concat("TESTS(", testClassName, ")\nTEST(", testName, ")");
      return testsAndTestLines;
   }
}

void ZenUnitEqualizer<ZenUnit::ClassNameTestName>::
AssertEqual(
   const ZenUnit::ClassNameTestName& expectedClassNameTestName,
   const ZenUnit::ClassNameTestName& actualClassNameTestName)
{
   ARE_EQUAL(expectedClassNameTestName.testClassName, actualClassNameTestName.testClassName);
   ARE_EQUAL(expectedClassNameTestName.testName, actualClassNameTestName.testName);
}
