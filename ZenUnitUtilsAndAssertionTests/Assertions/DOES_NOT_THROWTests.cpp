#include "pch.h"

namespace ZenUnit
{
   TESTS(DOES_NOT_THROWTests)
   AFACT(LambdaCallThrowsException_ThrowsException)
   AFACT(LambdaCallThrowsException_ThrowsException__MessagesTestCase)
   AFACT(FunctionCallThrowsException_ThrowsAnomaly)
   AFACT(LambdaCallDoesNotThrowException_DoesNotThrowException)
   AFACT(FunctionCallDoesNotThrowException_DoesNotThrowException)
   EVIDENCE

   TEST(LambdaCallThrowsException_ThrowsException)
   {
      THROWS_EXCEPTION(DOES_NOT_THROW([] { throw runtime_error("what text"); }()), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW([] { throw runtime_error(\"what text\"); }())",
"Expected: No exception was thrown",
"  Actual: std::runtime_error thrown",
"  what(): \"what text\"",
"File.cpp(1)"));
   }

   TEST(LambdaCallThrowsException_ThrowsException__MessagesTestCase)
   {
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(DOES_NOT_THROW([] { throw runtime_error(""); }(), messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW([] { throw runtime_error(\"\"); }(), messageA, messageB)",
"Expected: No exception was thrown",
"  Actual: std::runtime_error thrown",
"  what(): \"\"",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   void FunctionThatThrowsAnInvalidArgumentException()
   {
      throw invalid_argument("what text");
   }

   TEST(FunctionCallThrowsException_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(DOES_NOT_THROW(FunctionThatThrowsAnInvalidArgumentException()),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_NOT_THROW(FunctionThatThrowsAnInvalidArgumentException())",
"Expected: No exception was thrown",
"  Actual: std::invalid_argument thrown",
"  what(): \"what text\"",
"File.cpp(1)"));
   }

   TEST(LambdaCallDoesNotThrowException_DoesNotThrowException)
   {
      DOES_NOT_THROW([]{}());
   }

   void FunctionThatDoesNotThrowAnException() {}

   TEST(FunctionCallDoesNotThrowException_DoesNotThrowException)
   {
      DOES_NOT_THROW(FunctionThatDoesNotThrowAnException());
   }

   RUN_TESTS(DOES_NOT_THROWTests)
}
