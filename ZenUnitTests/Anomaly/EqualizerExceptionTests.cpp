#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   FACT(EqualizerException_what_ReturnsEmptyString)
   EVIDENCE

   TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   RUNTESTS(EqualizerExceptionTests)
}
