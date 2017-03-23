#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   SPEC(what_ReturnsEmptyString)
   SPECEND

   TEST(what_ReturnsEmptyString)
   {
      EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   }; RUN(EqualizerExceptionTests)
}
