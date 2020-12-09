#include "pch.h"

namespace ZenUnit
{
   TESTS(AssertTrueTests)
   AFACT(ZENUNIT_ASSERT_IsTrue_DoesNothing)
   EVIDENCE

   TEST(ZENUNIT_ASSERT_IsTrue_DoesNothing)
   {
      ZENUNIT_ASSERT(true);
      const bool trueBool = true;
      ZENUNIT_ASSERT(trueBool);
      ZENUNIT_ASSERT(1 == 1);
   }

   RUN_TESTS(AssertTrueTests)
}
