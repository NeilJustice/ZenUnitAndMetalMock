#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Assertions/REGEX_MATCHES.h"

namespace ZenUnit
{
   TESTS(STD_FUNCTION_TARGETSTests)
   AFACT(FunctionDoesNotPointToAFunction_ThrowsAnomaly__MessagesTestsCase)
   AFACT(FunctionPointsToFunctionWithDifferentSignatureThanExpected_ThrowsAnomaly)
   AFACT(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_ThrowsAnomaly)
   AFACT(FunctionPointsToSameFunctionAsExpected_DoesNotThrowException)
   AFACT(FunctionABC_CodeCoverage)
   EVIDENCE

   static void FunctionA() {}

   static void FunctionB(int) {}

   static void FunctionC()
   {
      // Side effect to ensure FunctionA and FunctionC have different addresses.
      // Otherwise the Release MSVC linker folds together blank FunctionA and blank FunctionC
      // resulting in FunctionA and FunctionC having the same address.
      cout << ' ';
   }

   TEST(FunctionDoesNotPointToAFunction_ThrowsAnomaly__MessagesTestsCase)
   {
      const function<void()> emptyStdFunction;
      const string messageA = "A", messageB = "B";
      try
      {
         STD_FUNCTION_TARGETS(FunctionA, emptyStdFunction, messageA, messageB);
         FAIL_TEST("STD_FUNCTION_TARGETS() did not throw Anomaly"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         string expectedPattern;
#if defined __linux__ || defined __APPLE__
         expectedPattern = "1";
#elif defined _WIN32
         expectedPattern = "0x\\w{16}";
#endif
         REGEX_MATCHES(TestUtil::NewlineConcat("",
"  Failed: STD_FUNCTION_TARGETS\\(FunctionA, emptyStdFunction, messageA, messageB\\)",
"Expected: " + expectedPattern,
"  Actual: <empty std::function>",
" Because: IS_TRUE\\(stdFunction\\) failed",
"Expected: true",
"  Actual: false",
" Message: \"A\", \"B\"",
"File.cpp\\(1\\)",
"File.cpp\\(1\\)"), anomaly.why);
      }
   }

   TEST(FunctionPointsToFunctionWithDifferentSignatureThanExpected_ThrowsAnomaly)
   {
      const function<void()> stdFunctionA(FunctionA);
      try
      {
         STD_FUNCTION_TARGETS(FunctionB, stdFunctionA);
         FAIL_TEST("STD_FUNCTION_TARGETS() did not throw Anomaly"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         string expectedPattern;
#if defined __linux__ || defined __APPLE__
         expectedPattern = "1";
#elif defined _WIN32
         expectedPattern = "0x\\w{16}";
#endif
         REGEX_MATCHES(TestUtil::NewlineConcat("",
"  Failed: STD_FUNCTION_TARGETS\\(FunctionB, stdFunctionA\\)",
"Expected: " + expectedPattern,
"  Actual: <non-empty std::function>",
" Because: IS_NOT_NULLPTR\\(stdFunction.template target<ExpectedStdFunctionTargetType\\*>\\(\\)\\) failed",
"Expected: not nullptr",
"  Actual: nullptr",
"File.cpp\\(1\\)",
"File.cpp\\(1\\)"), anomaly.why);
      }
   }

   TEST(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_ThrowsAnomaly)
   {
      const function<void()> stdFunctionA(FunctionA);

#if defined __linux__ || defined __APPLE__

      THROWS_EXCEPTION(STD_FUNCTION_TARGETS(FunctionC, stdFunctionA), Anomaly, TestUtil::NewlineConcat("",
"  Failed: STD_FUNCTION_TARGETS(FunctionC, stdFunctionA)",
"Expected: 1",
"  Actual: <non-empty std::function>",
" Because: ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>()) failed",
"Expected: 1",
"  Actual: 1",
"File.cpp(1)",
"File.cpp(1)"));

#elif defined _WIN32
      try
      {
         STD_FUNCTION_TARGETS(FunctionC, stdFunctionA);
         FAIL_TEST("STD_FUNCTION_TARGETS() did not throw Anomaly"); // LCOV_EXCL_LINE
      }
      catch (const Anomaly& anomaly)
      {
         REGEX_MATCHES(TestUtil::NewlineConcat("",
"  Failed: STD_FUNCTION_TARGETS\\(FunctionC, stdFunctionA\\)",
"Expected: 0x\\w{16}",
"  Actual: <non-empty std::function>",
" Because: ARE_EQUAL\\(expectedStdFunctionTarget, \\*stdFunction\\.template target<ExpectedStdFunctionTargetType\\*>\\(\\)\\) failed",
"Expected: 0x\\w{16}",
"  Actual: 0x\\w{16}",
"File.cpp\\(1\\)",
"File.cpp\\(1\\)"), anomaly.why);
      }

#endif
   }

   TEST(FunctionPointsToSameFunctionAsExpected_DoesNotThrowException)
   {
      const function<void()> stdFunctionA(FunctionA);
      STD_FUNCTION_TARGETS(FunctionA, stdFunctionA);
   }

   TEST(FunctionABC_CodeCoverage)
   {
      FunctionA();
      FunctionB(0);
      FunctionC();
   }

   RUN_TESTS(STD_FUNCTION_TARGETSTests)
}
