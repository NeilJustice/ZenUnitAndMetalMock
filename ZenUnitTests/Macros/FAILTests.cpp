#include "pch.h"
#include "ZenUnit/Macros/FAIL.h"

namespace ZenUnit
{
   TESTS(FAILTests)
   FACT(StringLiteralBecause_Throws)
   FACT(StringVariableBecause_MessagesTestCase_Throws)
   BEGINPROOF

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

   }; RUN(FAILTests)
}
