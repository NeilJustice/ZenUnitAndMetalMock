#include "pch.h"
#include "ZenUnitLibraryTests/Random/RandomFullTestName.h"

namespace ZenUnit
{
   template<>
   FullTestName Random<FullTestName>()
   {
      FullTestName randomFullTestName;
      randomFullTestName.testClassName = reinterpret_cast<const char*>(&randomFullTestName.testClassName);
      randomFullTestName.testName = reinterpret_cast<const char*>(&randomFullTestName.testName);
      randomFullTestName.arity = ZenUnit::RandomNon0<unsigned char>();
      return randomFullTestName;
   }
}
