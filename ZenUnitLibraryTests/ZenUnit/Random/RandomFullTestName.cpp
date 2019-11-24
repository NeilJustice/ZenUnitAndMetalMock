#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFullTestName.h"

namespace ZenUnit
{
   template<>
   FullTestName Random<FullTestName>()
   {
      return TestableRandomFullTestName(RandomGenerator());
   }

   FullTestName TestableRandomFullTestName(const RandomGenerator& randomGenerator)
   {
      FullTestName randomFullTestName;
      randomFullTestName.testClassName = randomGenerator.ConstCharPointer();
      randomFullTestName.testName = randomGenerator.ConstCharPointer();
      randomFullTestName.arity = randomGenerator.UnsignedChar();
      return randomFullTestName;
   }
}
