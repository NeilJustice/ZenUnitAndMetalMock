#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFullTestName.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"

namespace ZenUnit
{
   TESTS(RandomFullTestNameTests)
   AFACT(RandomFullTestName_CodeCoverage)
   AFACT(TestableRandomFullTestName_ReturnsFullTestNameWithAllRandomFields)
   EVIDENCE

   TEST(RandomFullTestName_CodeCoverage)
   {
      ZenUnit::Random<FullTestName>();
   }

   TEST(TestableRandomFullTestName_ReturnsFullTestNameWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const char* const testClassName = ZenUnit::Random<const char*>();
      const char* const testName = ZenUnit::Random<const char*>();
      randomGeneratorMock.ConstCharPointerMock.ReturnValues(testClassName, testName);

      const unsigned char arity = randomGeneratorMock.UnsignedCharMock.ReturnRandom();
      //
      const FullTestName randomFullTestName = TestableRandomFullTestName(randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.ConstCharPointerMock.CalledNTimes(2));
      METALMOCK(randomGeneratorMock.UnsignedCharMock.CalledOnce());
      FullTestName expectedRandomFullTestName;
      expectedRandomFullTestName.testClassName = testClassName;
      expectedRandomFullTestName.testName = testName;
      expectedRandomFullTestName.arity = arity;
      ARE_EQUAL(expectedRandomFullTestName, randomFullTestName);
   }

   RUN_TESTS(RandomFullTestNameTests)
}
