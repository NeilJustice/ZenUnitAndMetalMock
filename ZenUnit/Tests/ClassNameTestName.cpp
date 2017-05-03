#include "pch.h"
#include "ClassNameTestName.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   ClassNameTestName::ClassNameTestName()
      : testClassName(nullptr)
      , testName(nullptr)
      , arity(0)
   {
   }

   ClassNameTestName::ClassNameTestName(const char* testClassName, const char* testName, unsigned char arity)
      : testClassName(testClassName)
      , testName(testName)
      , arity(arity)
   {
   }

   string ClassNameTestName::Value() const
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

void ZenUnitEqualizer<ZenUnit::ClassNameTestName>::
AssertEqual(
   const ZenUnit::ClassNameTestName& expectedClassNameTestName,
   const ZenUnit::ClassNameTestName& actualClassNameTestName)
{
   ARE_EQUAL(expectedClassNameTestName.testClassName, actualClassNameTestName.testClassName);
   ARE_EQUAL(expectedClassNameTestName.testName, actualClassNameTestName.testName);
   ARE_EQUAL(expectedClassNameTestName.arity, actualClassNameTestName.arity);
}
