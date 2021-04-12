#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FullTestName>::AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName)
   {
      FIELDS_ARE_EQUAL(expectedFullTestName, actualFullTestName, testClassName);
      FIELDS_ARE_EQUAL(expectedFullTestName, actualFullTestName, testName);
      FIELDS_ARE_EQUAL(expectedFullTestName, actualFullTestName, arity);
   }

   FullTestName TestableRandomFullTestName(const ZenUnit::RandomGenerator* randomGenerator)
   {
      FullTestName randomFullTestName;
      randomFullTestName.testClassName = randomGenerator->ConstCharPointer();
      randomFullTestName.testName = randomGenerator->ConstCharPointer();
      randomFullTestName.arity = randomGenerator->UnsignedChar();
      return randomFullTestName;
   }

   template<>
   FullTestName Random()
   {
      return TestableRandomFullTestName(ZenUnit::RandomGenerator::Instance());
   }
}
