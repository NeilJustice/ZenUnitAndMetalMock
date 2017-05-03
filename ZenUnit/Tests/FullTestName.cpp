#include "pch.h"
#include "FullTestName.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   FullTestName::FullTestName()
      : testClassName(nullptr)
      , testName(nullptr)
      , arity(0)
   {
   }

   FullTestName::FullTestName(const char* testClassName, const char* testName, unsigned char arity)
      : testClassName(testClassName)
      , testName(testName)
      , arity(arity)
   {
   }

   string FullTestName::Value() const
   {
      if (arity == 0)
      {
         const string fullTestName = String::Concat("TESTS(", testClassName, ")\nTEST(", testName, ')');
         return fullTestName;
      }
      else
      {
         const string fullTestName = String::Concat(
            "TESTS(", testClassName, ")\nTEST", static_cast<int>(arity), 'X', static_cast<int>(arity), '(', testName, ')');
         return fullTestName;
      }
   }
}

void ZenUnitEqualizer<ZenUnit::FullTestName>::
AssertEqual(
   const ZenUnit::FullTestName& expectedFullTestName,
   const ZenUnit::FullTestName& actualFullTestName)
{
   ARE_EQUAL(expectedFullTestName.testClassName, actualFullTestName.testClassName);
   ARE_EQUAL(expectedFullTestName.testName, actualFullTestName.testName);
   ARE_EQUAL(expectedFullTestName.arity, actualFullTestName.arity);
}
