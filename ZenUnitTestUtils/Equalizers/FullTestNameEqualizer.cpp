#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"

namespace ZenUnit
{
   void Equalizer<FullTestName>::AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName)
   {
      ARE_EQUAL(expectedFullTestName.testClassName, actualFullTestName.testClassName);
      ARE_EQUAL(expectedFullTestName.testName, actualFullTestName.testName);
      ARE_EQUAL(expectedFullTestName.arity, actualFullTestName.arity);
   }
};
