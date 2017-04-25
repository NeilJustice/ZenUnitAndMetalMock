#include "pch.h"
#include "ZenUnit/Tests/ClassNameTestName.h"

namespace ZenUnit
{
   TESTS(ClassNameTestNameTests)
   SPEC(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   SPEC(TwoArgConstructor_SetsClassNameAndTestName)
   SPEC(TestsAndTestLines_ReturnsExpected)
   SPEC(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   {
      const ClassNameTestName defaultTestName;
      ClassNameTestName expectedDefaultTestName;
      expectedDefaultTestName.testClassName = nullptr;
      expectedDefaultTestName.testName = nullptr;
      ARE_EQUAL(expectedDefaultTestName, defaultTestName);
   }

   TEST(TwoArgConstructor_SetsClassNameAndTestName)
   {
      const ClassNameTestName testName("TestClassName", "TestName");
      ClassNameTestName expectedTestName;
      expectedTestName.testClassName = "TestClassName";
      expectedTestName.testName = "TestName";
      ARE_EQUAL(expectedTestName, testName);
   }

   TEST(TestsAndTestLines_ReturnsExpected)
   {
      const ClassNameTestName testName("TestClassName", "TestName");
      ARE_EQUAL(
         "TESTS(TestClassName)\n"
         "TEST(TestName)", testName.TestsAndTestLines());
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      EQUALIZER_THROWS_INIT(ClassNameTestName);
      EQUALIZER_THROWS(ClassNameTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS(ClassNameTestName, testName, "TestName");
   }

   }; RUN(ClassNameTestNameTests)
}
