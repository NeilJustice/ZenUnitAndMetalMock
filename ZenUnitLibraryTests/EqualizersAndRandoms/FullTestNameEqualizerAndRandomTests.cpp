#include "pch.h"

namespace ZenUnit
{
   TESTS(FullTestNameEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomFullTestName_ReturnsFullTestNameWithAllRandomFields)
   AFACT(RandomFullTestName_DoesNotThrowException)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(FullTestName);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FullTestName, testClassName, ZenUnit::Random<const char*>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FullTestName, testName, ZenUnit::Random<const char*>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FullTestName, arity, ZenUnit::RandomNon0<unsigned char>());
   }

   TEST(TestableRandomFullTestName_ReturnsFullTestNameWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const char* const testClassName = ZenUnit::Random<const char*>();
      const char* const testName = ZenUnit::Random<const char*>();
      randomGeneratorMock.ConstCharPointerMock.ReturnValues(testClassName, testName);

      const unsigned char arity = randomGeneratorMock.UnsignedCharMock.ReturnRandom();
      //
      const FullTestName randomFullTestName = TestableRandomFullTestName(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.ConstCharPointerMock.CalledNTimes(2));
      METALMOCK(randomGeneratorMock.UnsignedCharMock.CalledOnce());
      FullTestName expectedRandomFullTestName;
      expectedRandomFullTestName.testClassName = testClassName;
      expectedRandomFullTestName.testName = testName;
      expectedRandomFullTestName.arity = arity;
      ARE_EQUAL(expectedRandomFullTestName, randomFullTestName);
   }

   TEST(RandomFullTestName_DoesNotThrowException)
   {
      ZenUnit::Random<FullTestName>();
   }

   RUN_TESTS(FullTestNameEqualizerAndRandomTests)
}
