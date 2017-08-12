#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   FACT(EqualizerException_what_ReturnsEmptyString)
   BEGINPROOF

   TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   }; RUN(EqualizerExceptionTests)
}
