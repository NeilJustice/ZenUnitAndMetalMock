#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FullTestName>::AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName)
   {
      ARE_EQUAL(expectedFullTestName.testClassName, actualFullTestName.testClassName);
      ARE_EQUAL(expectedFullTestName.testName, actualFullTestName.testName);
      ARE_EQUAL(expectedFullTestName.arity, actualFullTestName.arity);
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
};
