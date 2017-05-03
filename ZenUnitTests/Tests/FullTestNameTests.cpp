#include "pch.h"
#include "ZenUnit/Tests/FullTestName.h"

namespace ZenUnit
{
   TESTS(FullTestNameTests)
   SPEC(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   SPEC(ThreeArgConstructor_SetsFields)
   SPECX(Value_ReturnsExpected)
   SPEC(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   {
      const FullTestName defaultTestName;
      FullTestName expectedDefaultTestName;
      expectedDefaultTestName.testClassName = nullptr;
      expectedDefaultTestName.testName = nullptr;
      expectedDefaultTestName.arity = 0;
      ARE_EQUAL(expectedDefaultTestName, defaultTestName);
   }

   TEST(ThreeArgConstructor_SetsFields)
   {
      const FullTestName testName("TestClassName", "TestName", 1);
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
      const FullTestName testName("Tests", "Test", arity);
      string expectedValue = "TESTS(Tests)\n" + 
         expectedTestTypeName + "(Test)";
      ARE_EQUAL(expectedValue, testName.Value());
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      EQUALIZER_THROWS_INIT(FullTestName);
      EQUALIZER_THROWS(FullTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS(FullTestName, testName, "TestName");
      EQUALIZER_THROWS(FullTestName, arity, unsigned char(1));
   }

   }; RUN(FullTestNameTests)
}
