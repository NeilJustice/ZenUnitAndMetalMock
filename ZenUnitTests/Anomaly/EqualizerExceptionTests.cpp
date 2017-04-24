#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   SPEC(EqualizerException_what_ReturnsEmptyString)
   SPECEND

   TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   }; RUN(EqualizerExceptionTests)
}
