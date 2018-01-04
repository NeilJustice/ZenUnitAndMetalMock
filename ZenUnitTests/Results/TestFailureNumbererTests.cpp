#include "pch.h"

namespace ZenUnit
{
   TESTS(TestFailureNumbererTests)
   AFACT(TestFailureNumberer_NextReturnsIncrementingAngleBracketedSequence)
   EVIDENCE

   TEST(TestFailureNumberer_NextReturnsIncrementingAngleBracketedSequence)
   {
      TestFailureNumberer testFailureNumberer;
      ARE_EQUAL("Test Failure 1:", testFailureNumberer.Next());
      ARE_EQUAL("Test Failure 2:", testFailureNumberer.Next());
      ARE_EQUAL("Test Failure 3:", testFailureNumberer.Next());
      testFailureNumberer.Reset();
      ARE_EQUAL("Test Failure 1:", testFailureNumberer.Next());
      ARE_EQUAL("Test Failure 2:", testFailureNumberer.Next());
      ARE_EQUAL("Test Failure 3:", testFailureNumberer.Next());
   }

   }; RUNTESTS(TestFailureNumbererTests)
}
