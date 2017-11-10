#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Tests/FullTestName.h"

namespace ZenUnit
{
   INLINE FullTestName::FullTestName()
      : testClassName(nullptr)
      , testName(nullptr)
      , arity(0)
   {
   }

   INLINE FullTestName::FullTestName(const char* testClassName, const char* testName, unsigned char arity)
      : testClassName(testClassName)
      , testName(testName)
      , arity(arity)
   {
   }

   INLINE std::string FullTestName::Value() const
   {
      const bool testClassIsTemplated = String::Contains(testClassName, "<");
      const char* const testsOrTemplateTests = testClassIsTemplated ? "TEMPLATETESTS(" : "TESTS(";
      if (arity == 0)
      {
         const std::string fullTestName = String::Concat(testsOrTemplateTests, testClassName, ")\nTEST(", testName, ')');
         return fullTestName;
      }
      const std::string fullTestName = String::Concat(
         testsOrTemplateTests, testClassName, ")\nTEST", static_cast<int>(arity), 'X', static_cast<int>(arity), '(', testName, ')');
      return fullTestName;
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::FullTestName>::
AssertEqual(
   const ZenUnit::FullTestName& expectedFullTestName,
   const ZenUnit::FullTestName& actualFullTestName)
{
   ARE_EQUAL(expectedFullTestName.testClassName, actualFullTestName.testClassName);
   ARE_EQUAL(expectedFullTestName.testName, actualFullTestName.testName);
   ARE_EQUAL(expectedFullTestName.arity, actualFullTestName.arity);
}
