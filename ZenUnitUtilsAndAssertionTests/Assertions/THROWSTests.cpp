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

   const string MessageA = "A", MessageB = "B";

   TEST(CallDoesNotThrow_Throws)
   {
      try
      {
         THROWS([]{}(), exception, "");
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{}(), exception,",
"          \"\")",
"Expected thrown: std::exception exactly",
"  Actual thrown: No exception thrown",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallDoesNotThrow_Throws_MessagesTestCase)
   {
      try
      {
         THROWS([]{}(), exception, "", MessageA, MessageB);
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{}(), exception,",
"          \"\", MessageA, MessageB)",
"Expected thrown: std::exception exactly",
"  Actual thrown: No exception thrown",
" Message: \"A\", \"B\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsSubclassOfExpectedException_Throws)
   {
      try
      {
         THROWS([]{ throw logic_error(""); }(), exception, "");
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{ throw logic_error(\"\"); }(), exception,",
"          \"\")",
"Expected thrown: std::exception exactly",
"  Actual thrown: std::logic_error",
"  what(): \"\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsNonSubclassOfExpectedException_Throws)
   {
      try
      {
         THROWS([]{ throw runtime_error("what"); }(), logic_error, "");
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{ throw runtime_error(\"what\"); }(), logic_error,",
"          \"\")",
"Expected thrown: std::logic_error exactly",
"  Actual thrown: std::runtime_error",
"  what(): \"what\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatDoesNotMatch_Throws)
   {
      try
      {
         THROWS([]{ throw runtime_error("what"); }(), runtime_error, "");
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{ throw runtime_error(\"what\"); }(), runtime_error,",
"          \"\")",
"Expected thrown: std::runtime_error exactly",
"  Actual thrown: std::runtime_error exactly",
"Expected what(): \"\"",
"  Actual what(): \"what\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatTextMatchesExceptForCase_Throws)
   {
      try
      {
         THROWS([]{ throw runtime_error("hello"); }(), runtime_error, "Hello");
         FAIL_TEST("THROWS() did not throw");
      }
      catch (const Anomaly& anomaly)
      {
         ARE_EQUAL(TestUtil::NewlineConcat("",
"  Failed: THROWS([]{ throw runtime_error(\"hello\"); }(), runtime_error,",
"          \"Hello\")",
"Expected thrown: std::runtime_error exactly",
"  Actual thrown: std::runtime_error exactly",
"Expected what(): \"Hello\"",
"  Actual what(): \"hello\"",
"File.cpp(1)"), anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedException_WhatTextMatchesExactly_DoesNotThrow)
   {
      THROWS([]{ throw runtime_error("what"); }(), runtime_error, "what");
      THROWS([]{ throw logic_error("what"); }(), logic_error, "what");
   }

   TEST(NeverThrownType_whatReturnsNullptr)
   {
      const NeverThrownType neverThrownType;
      IS_NULL(neverThrownType.what());
   }

   RUN_TESTS(THROWSTests)
}
