#include "pch.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
   AFACT(EqualizerException_what_ReturnsEmptyString)
   EVIDENCE

   static_assert(is_base_of_v<std::exception, EqualizerException>);

   TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

   RUN_TESTS(EqualizerExceptionTests)
}