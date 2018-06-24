#include "pch.h"

namespace ZenUnit
{
   TESTS(DOES_NOT_THROWTests)
   AFACT(LambdaCallThrows_Throws)
   AFACT(LambdaCallThrows_Throws_MessagesTestCase)
   AFACT(FunctionCallThrows_Throws)
   AFACT(LambdaCallDoesNotThrow_DoesNotThrow)
   AFACT(FunctionCallDoesNotThrow_DoesNotThrow)
   EVIDENCE

   TEST(LambdaCallThrows_Throws)
   {
      THROWS(DOES_NOT_THROW([] { throw runtime_error("what text"); }()), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW([] { throw runtime_error(\"what text\"); }())",
"Expected: No exception thrown",
"  Actual: std::runtime_error thrown",
"  what(): \"what text\"",
"File.cpp(1)"));
   }

   TEST(LambdaCallThrows_Throws_MessagesTestCase)
   {
      const string MessageA = "A", MessageB = "B";
      THROWS(DOES_NOT_THROW([] { throw runtime_error(""); }(), MessageA, MessageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW([] { throw runtime_error(\"\"); }(), MessageA, MessageB)",
"Expected: No exception thrown",
"  Actual: std::runtime_error thrown",
"  what(): \"\"",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   void Throw()
   {
      throw invalid_argument("what text");
   }

   TEST(FunctionCallThrows_Throws)
   {
      THROWS(DOES_NOT_THROW(Throw()), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW(Throw())",
"Expected: No exception thrown",
"  Actual: std::invalid_argument thrown",
"  what(): \"what text\"",
"File.cpp(1)"));
   }

   TEST(LambdaCallDoesNotThrow_DoesNotThrow)
   {
      DOES_NOT_THROW([]{}());
   }

   void NoThrow() {}

   TEST(FunctionCallDoesNotThrow_DoesNotThrow)
   {
      DOES_NOT_THROW(NoThrow());
   }

   RUN_TESTS(DOES_NOT_THROWTests)
}
