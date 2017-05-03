#include "pch.h"
#include "ZenUnit/Tests/ClassNameTestName.h"

namespace ZenUnit
{
   TESTS(ClassNameTestNameTests)
   SPEC(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   SPEC(ThreeArgConstructor_SetsFields)
   SPECX(Value_ReturnsExpected)
   SPEC(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   {
      const ClassNameTestName defaultTestName;
      ClassNameTestName expectedDefaultTestName;
      expectedDefaultTestName.testClassName = nullptr;
      expectedDefaultTestName.testName = nullptr;
      expectedDefaultTestName.arity = 0;
      ARE_EQUAL(expectedDefaultTestName, defaultTestName);
   }

   TEST(ThreeArgConstructor_SetsFields)
   {
      const ClassNameTestName testName("TestClassName", "TestName", 1);
      ARE_EQUAL("TestClassName", testName.testClassName);
      ARE_EQUAL("TestName", testName.testName);
      ARE_EQUAL(1, testName.arity);
   }

   TEST2X2(Value_ReturnsExpected,
      unsigned char arity, const string& expectedTestTypeName,
      unsigned char(0), "TEST",
      unsigned char(1), "TEST1X1",
      unsigned char(2), "TEST2X2",
      unsigned char(3), "TEST3X3")
   {
      const ClassNameTestName testName("Tests", "Test", arity);
      string expectedValue = "TESTS(Tests)\n" + 
         expectedTestTypeName + "(Test)";
      ARE_EQUAL(expectedValue, testName.Value());
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      EQUALIZER_THROWS_INIT(ClassNameTestName);
      EQUALIZER_THROWS(ClassNameTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS(ClassNameTestName, testName, "TestName");
      EQUALIZER_THROWS(ClassNameTestName, arity, unsigned char(1));
   }

   }; RUN(ClassNameTestNameTests)
}
