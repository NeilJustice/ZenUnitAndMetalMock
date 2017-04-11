#include "pch.h"
#include "ZenUnit/Tests/FullName.h"

namespace ZenUnit
{
   TESTS(FullNameTests)
   SPEC(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   SPEC(TwoArgConstructor_SetsClassNameAndTestName)
   SPEC(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   {
      const FullName defaultTestName;
      FullName expectedDefaultTestName;
      expectedDefaultTestName.testClassName = nullptr;
      expectedDefaultTestName.testName = nullptr;
      expectedDefaultTestName.testClassTestNameLines = string();
      ARE_EQUAL(expectedDefaultTestName, defaultTestName);
   }

   TEST(TwoArgConstructor_SetsClassNameAndTestName)
   {
      const FullName testName("TestClassName", "TestName");
      FullName expectedTestName;
      expectedTestName.testClassName = "TestClassName";
      expectedTestName.testName = "TestName";
      expectedTestName.testClassTestNameLines =
   "TESTS(TestClassName)\n"
   "TEST(TestName)";
      ARE_EQUAL(expectedTestName, testName);
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      EQUALIZER_THROWS_INIT(FullName);
      EQUALIZER_THROWS(FullName, testClassName, "TestClassName");
      EQUALIZER_THROWS(FullName, testName, "TestName");
      EQUALIZER_THROWS(FullName, testClassTestNameLines, "testClassTestNameLines");
   }

   }; RUN(FullNameTests)
}
