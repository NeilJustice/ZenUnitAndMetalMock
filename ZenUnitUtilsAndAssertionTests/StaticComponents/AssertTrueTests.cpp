#include "pch.h"

namespace ZenUnit
{
   TESTS(AssertTrueTests)
   AFACT(ZENUNIT_ASSERT_IsTrue_DoesNotThrowException)
   EVIDENCE

   TEST(ZENUNIT_ASSERT_IsTrue_DoesNotThrowException)
   {
      ZENUNIT_ASSERT(true);
      const bool trueBool = true;
      ZENUNIT_ASSERT(trueBool);
   }

   RUN_TESTS(AssertTrueTests)
}
