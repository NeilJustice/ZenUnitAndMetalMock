#include "pch.h"

namespace ZenUnit
{
   TESTS(FAILTests)
   AFACT(StringLiteralBecause_Throws)
   AFACT(StringVariableBecause_MessagesTestCase_Throws)
   EVIDENCE

   TEST(StringLiteralBecause_Throws)
   {
      THROWS(FAIL("Because"), Anomaly, R"(
 Failed: FAIL("Because")
File.cpp(1))");
   }

   TEST(StringVariableBecause_MessagesTestCase_Throws)
   {
      const string Because = "BecauseValue";
      const string messageA = "A", messageB = "B";
      THROWS(FAIL(Because, messageA, messageB), Anomaly, R"(
 Failed: FAIL(Because, messageA, messageB)
Because: "BecauseValue"
Message: "A", "B"
File.cpp(1))");
   }

   }; RUNTESTS(FAILTests)
}
