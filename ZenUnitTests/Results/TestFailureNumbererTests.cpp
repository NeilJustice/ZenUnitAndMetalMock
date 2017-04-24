#include "pch.h"
#include "ZenUnit/Results/TestFailureNumberer.h"

namespace ZenUnit
{
   TESTS(TestFailureNumbererTests)
   SPEC(TestFailureNumberer_ConstructorAndNext_ReturnsAngleBracketWrappedIncrementingSequenceStartingFrom1)
   SPECEND

   TEST(TestFailureNumberer_ConstructorAndNext_ReturnsAngleBracketWrappedIncrementingSequenceStartingFrom1)
   {
      TestFailureNumberer testFailureNumberer;
      ARE_EQUAL("<1>", testFailureNumberer.Next());
      ARE_EQUAL("<2>", testFailureNumberer.Next());
      ARE_EQUAL("<3>", testFailureNumberer.Next());
   }

   }; RUN(TestFailureNumbererTests)
}
