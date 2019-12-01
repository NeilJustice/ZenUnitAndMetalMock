#include  "pch.h"

namespace ZenUnit
{
   TESTS(THROWS_EXCEPTIONTests)
   AFACT(CallDoesNotThrowException_ThrowsAnomaly)
   AFACT(CallDoesNotThrowException_ThrowsAnomaly_MessagesTestCase)
   AFACT(CallThrowsSubclassOfExpectedException_ThrowsAnomaly)
   AFACT(CallThrowsNonSubclassOfExpectedExceptionType_ThrowsAnomaly)
   AFACT(CallThrowsExactExpectedExceptionType_WhatTextDoesNotMatchExactly_ThrowsAnomaly)
   AFACT(CallThrowsExactExpectedExceptionType_WhatTextMatchesExceptForCase_ThrowsAnomaly)
   AFACT(CallThrowsExactExpectedExceptionType_ActualWhatTextContainsExpectedWhatTextAsAnExactSubstringMatchButNotAnEntireStringMatch_ThrowsAnomaly)
   AFACT(CallThrowsExactExpectedExceptionType_WhatTextMatchesExactly_DoesNotThrowException)
   AFACT(NeverThrownType_whatReturnsNullptr_CodeCoverage)
   EVIDENCE

   TEST(CallDoesNotThrowException_ThrowsAnomaly)
   {
      try
      {
         THROWS_EXCEPTION([]{}(), exception, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([]{}(), exception,",
            "          \"\")",
            "Expected exception thrown: std::exception exactly",
            "  Actual exception thrown: No exception was thrown",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallDoesNotThrowException_ThrowsAnomaly_MessagesTestCase)
   {
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      try
      {
         THROWS_EXCEPTION([]{}(), exception, "", messageA, messageB);
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([]{}(), exception,",
            "          \"\", messageA, messageB)",
            "Expected exception thrown: std::exception exactly",
            "  Actual exception thrown: No exception was thrown",
            " Message: \"" + messageA + "\", \"" + messageB + "\"",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallThrowsSubclassOfExpectedException_ThrowsAnomaly)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw logic_error(""); }(), exception, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([]{ throw logic_error(\"\"); }(), exception,",
            "          \"\")",
            "Expected exception thrown: std::exception exactly",
            "  Actual exception thrown: std::logic_error",
            "  what(): \"\"",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallThrowsNonSubclassOfExpectedExceptionType_ThrowsAnomaly)
   {
      const string whatText = ZenUnit::Random<string>();
      try
      {
         THROWS_EXCEPTION([&]{ throw runtime_error(whatText); }(), logic_error, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([&]{ throw runtime_error(whatText); }(), logic_error,",
            "          \"\")",
            "Expected exception thrown: std::logic_error exactly",
            "  Actual exception thrown: std::runtime_error",
            "  what(): \"" + whatText + "\"",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedExceptionType_WhatTextDoesNotMatchExactly_ThrowsAnomaly)
   {
      const string whatText = ZenUnit::Random<string>();
      try
      {
         THROWS_EXCEPTION([&]{ throw runtime_error(whatText); }(), runtime_error, "");
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([&]{ throw runtime_error(whatText); }(), runtime_error,",
            "          \"\")",
            "Expected exception thrown: std::runtime_error exactly",
            "  Actual exception thrown: std::runtime_error exactly",
            "Expected what(): \"\"",
            "  Actual what(): \"" + whatText + "\"",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedExceptionType_WhatTextMatchesExceptForCase_ThrowsAnomaly)
   {
      try
      {
         THROWS_EXCEPTION([]{ throw runtime_error("ERROR MESSAGE"); }(), runtime_error, "error message");
         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         const string expectedWhy = TestUtil::NewlineConcat("",
            "  Failed: THROWS_EXCEPTION([]{ throw runtime_error(\"ERROR MESSAGE\"); }(), runtime_error,",
            "          \"error message\")",
            "Expected exception thrown: std::runtime_error exactly",
            "  Actual exception thrown: std::runtime_error exactly",
            "Expected what(): \"error message\"",
            "  Actual what(): \"ERROR MESSAGE\"",
            "File.cpp(1)");
         ARE_EQUAL(expectedWhy, anomaly.why);
      }
   }

   TEST(CallThrowsExactExpectedExceptionType_ActualWhatTextContainsExpectedWhatTextAsAnExactSubstringMatchButNotAnEntireStringMatch_ThrowsAnomaly)
   {
//      try
//      {
//         THROWS_EXCEPTION([] { throw runtime_error("timestamp E123: error message"); }(),
//            runtime_error, "error message");
//         FAIL_TEST("THROWS_EXCEPTION() did not throw Anomaly as expected"); // LCOV_EXCL_LINE
//      }
//      catch (const Anomaly & anomaly)
//      {
//         ARE_EQUAL(TestUtil::NewlineConcat("",
//"  Failed: THROWS_EXCEPTION([]{ throw runtime_error(\"timestamp E123: error message\"); }(), runtime_error,",
//"          \"error message\")",
//"Expected exception thrown: std::runtime_error exactly",
//"  Actual exception thrown: std::runtime_error exactly",
//"Expected what(): \"error message\"",
//"  Actual what(): \"timestamp E123: error message\"",
//"File.cpp(1)"), anomaly.why);
//      }
   }

   TEST(CallThrowsExactExpectedExceptionType_WhatTextMatchesExactly_DoesNotThrowException)
   {
      const string whatText = ZenUnit::Random<string>();
      THROWS_EXCEPTION([&]{ throw runtime_error(whatText); }(), runtime_error, whatText);
      THROWS_EXCEPTION([&]{ throw logic_error(whatText); }(), logic_error, whatText);
   }

   TEST(NeverThrownType_whatReturnsNullptr_CodeCoverage)
   {
      const ZenUnit::NeverThrownType neverThrownType;
      POINTER_IS_NULL(neverThrownType.what());
   }

   RUN_TESTS(THROWS_EXCEPTIONTests)
}
