#include  "pch.h"

namespace ZenUnit
{
   TESTS(THROWSTests)
   AFACT(CallDoesNotThrow_Throws)
   AFACT(CallDoesNotThrow_Throws_MessagesTestCase)
   AFACT(CallThrowsSubclassOfExpectedException_Throws)
   AFACT(CallThrowsNonSubclassOfExpectedException_Throws)
   AFACT(CallThrowsExactExpectedException_WhatDoesNotMatch_Throws)
   AFACT(CallThrowsExactExpectedException_WhatTextMatchesExceptForCase_Throws)
   AFACT(CallThrowsExactExpectedException_WhatTextMatchesExactly_DoesNotThrow)
   AFACT(NeverThrownType_whatReturnsNullptr)
   EVIDENCE

   const string _messageA = "A";
   const string _messageB = "B";

   TEST(CallDoesNotThrow_Throws)
   {
      try
      {
         THROWS_EXCEPTION([]{}(), exception, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{}(), exception,",
"          \"\")",
"Expected exception thrown: std::exception exactly",
"  Actual exception thrown: No exception thrown",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallDoesNotThrow_Throws_MessagesTestCase)
   {
      try
      {
         THROWS_EXCEPTION([]{}(), exception, "", _messageA, _messageB);
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{}(), exception,",
"          \"\", _messageA, _messageB)",
"Expected exception thrown: std::exception exactly",
"  Actual exception thrown: No exception thrown",
" Message: \"A\", \"B\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsSubclassOfExpectedException_Throws)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw logic_error(""); }(), exception, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{ throw logic_error(\"\"); }(), exception,",
"          \"\")",
"Expected exception thrown: std::exception exactly",
"  Actual exception thrown: std::logic_error",
"  what(): \"\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsNonSubclassOfExpectedException_Throws)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw runtime_error("what"); }(), logic_error, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{ throw runtime_error(\"what\"); }(), logic_error,",
"          \"\")",
"Expected exception thrown: std::logic_error exactly",
"  Actual exception thrown: std::runtime_error",
"  what(): \"what\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatDoesNotMatch_Throws)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw runtime_error("what"); }(), runtime_error, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{ throw runtime_error(\"what\"); }(), runtime_error,",
"          \"\")",
"Expected exception thrown: std::runtime_error exactly",
"  Actual exception thrown: std::runtime_error exactly",
"Expected what(): \"\"",
"  Actual what(): \"what\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatTextMatchesExceptForCase_Throws)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw runtime_error("hello"); }(), runtime_error, "Hello");
         FAIL_TEST("THROWS_EXCEPTION() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS_EXCEPTION([]{ throw runtime_error(\"hello\"); }(), runtime_error,",
"          \"Hello\")",
"Expected exception thrown: std::runtime_error exactly",
"  Actual exception thrown: std::runtime_error exactly",
"Expected what(): \"Hello\"",
"  Actual what(): \"hello\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatTextMatchesExactly_DoesNotThrow)
   {
      THROWS_EXCEPTION([]{ throw runtime_error("what"); }(), runtime_error, "what");
      THROWS_EXCEPTION([]{ throw logic_error("what"); }(), logic_error, "what");
   }

   TEST(NeverThrownType_whatReturnsNullptr)
   {
      const NeverThrownType neverThrownType;
      POINTER_IS_NULL(neverThrownType.what());
   }

   RUN_TESTS(THROWSTests)
}
