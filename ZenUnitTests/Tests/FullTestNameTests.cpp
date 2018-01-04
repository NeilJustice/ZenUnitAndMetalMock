#include "pch.h"

namespace ZenUnit
{
   TESTS(FullTestNameTests)
   AFACT(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   AFACT(ThreeArgConstructor_SetsFields)
   FACTS(Value_ReturnsExpected)
   AFACT(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   EVIDENCE

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
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      //
      const FullTestName testName(TestClassName.c_str(), TestName.c_str(), 1);
      //
      ARE_EQUAL(TestClassName, testName.testClassName);
      ARE_EQUAL(TestName, testName.testName);
      ARE_EQUAL(1, testName.arity);
   }

   TEST3X3(Value_ReturnsExpected,
      const string& expectedReturnValue, const char* testClassMacroArgument, unsigned char arity,
      "TESTS(Tests)\nTEST(Test)", "Tests", static_cast<unsigned char>(0),
      "TESTS(Tests)\nTEST1X1(Test)", "Tests", static_cast<unsigned char>(1),
      "TESTS(Tests)\nTEST2X2(Test)", "Tests", static_cast<unsigned char>(2),
      "TEMPLATETESTS(Tests<int>)\nTEST(Test)", "Tests<int>", static_cast<unsigned char>(0),
      "TEMPLATETESTS(Tests<int, int>)\nTEST1X1(Test)", "Tests<int, int>", static_cast<unsigned char>(1),
      "TEMPLATETESTS(Tests<vector<int>>)\nTEST2X2(Test)", "Tests<vector<int>>", static_cast<unsigned char>(2))
   {
      const FullTestName testName(testClassMacroArgument, "Test", arity);
      //
      const string value = testName.Value();
      //
      ARE_EQUAL(expectedReturnValue, value);
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(FullTestName);
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, testName, "TestName");
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, arity, static_cast<unsigned char>(1));
   }

   }; RUNTESTS(FullTestNameTests)
}
