#include "pch.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   AFACT(EqualizerException_what_ReturnsEmptyString)
   EVIDENCE

   TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   }; RUNTESTS(EqualizerExceptionTests)
}
