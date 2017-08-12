#include "pch.h"
#include "ZenUnit/Tests/FullTestName.h"
#include "ZenUnit/Utils/Random.h"

namespace ZenUnit
{
   TESTS(FullTestNameTests)
   FACT(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   FACT(ThreeArgConstructor_SetsFields)
   FACTS(Value_ReturnsExpected)
   FACT(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   BEGINPROOF

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
      "TEMPLATETESTS(Tests<std::vector<int>>)\nTEST2X2(Test)", "Tests<std::vector<int>>", static_cast<unsigned char>(2))
   {
      const FullTestName testName(testClassMacroArgument, "Test", arity);
      //
      const string value = testName.Value();
      //
      ARE_EQUAL(expectedReturnValue, value);
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      EQUALIZER_THROWS_INIT(FullTestName);
      EQUALIZER_THROWS(FullTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS(FullTestName, testName, "TestName");
      EQUALIZER_THROWS(FullTestName, arity, static_cast<unsigned char>(1));
   }

   }; RUN(FullTestNameTests)
}
