#include "pch.h"
#include "ZenUnit/Macros/FUNCTION_TARGETS.h"

namespace ZenUnit
{
   TESTS(FUNCTION_TARGETSTests)
   SPEC(FunctionDoesNotPointToAFunction_Throws_MessagesTestsCase)
   SPEC(FunctionPointsToFunctionWithDifferentSignatureThanExpected_Throws)
   SPEC(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_Throws)
   SPEC(FunctionPointsToSameFunctionAsExpected_DoesNotThrow)
   SPEC(FunctionABC_CodeCoverage)
   SPECEND

   static void FunctionA() {}
   static void FunctionB(int) {}
   static void FunctionC()
   {
      // Side effect to ensure FunctionA and FunctionC have different addresses.
      // Otherwise the Release MSVC linker folds together blank FunctionA and blank FunctionC
      // resulting in FunctionA and FunctionC having the same address.
      cout << ' ';
   }

   TEST(FunctionDoesNotPointToAFunction_Throws_MessagesTestsCase)
   {
      const function<void()> emptyStdFunction;
      const string messageA = "A", messageB = "B";
      try
      {
         FUNCTION_TARGETS(FunctionA, emptyStdFunction, messageA, messageB);
         FAIL("FUNCTION_TARGETS() did not throw Anomaly");
      }
      catch (const Anomaly& anomaly)
      {
#ifdef __linux__
         REGEX_MATCHES(R"(
  Failed: FUNCTION_TARGETS\(FunctionA, emptyStdFunction, messageA, messageB\)
Expected: 1
  Actual: <empty std::function>
 Because: IS_TRUE\(stdFunction\) failed
Expected: true
  Actual: false
 Message: "A", "B"
File.cpp\(1\)
File.cpp\(1\))", anomaly.why);
#elif _WIN32
         REGEX_MATCHES(R"(
  Failed: FUNCTION_TARGETS\(FunctionA, emptyStdFunction, messageA, messageB\)
Expected: 0x\w{16}
  Actual: <empty std::function>
 Because: IS_TRUE\(stdFunction\) failed
Expected: true
  Actual: false
 Message: "A", "B"
File.cpp\(1\)
File.cpp\(1\))", anomaly.why);
#endif
      }
   }

   TEST(FunctionPointsToFunctionWithDifferentSignatureThanExpected_Throws)
   {
      const function<void()> stdFunctionA(FunctionA);
      try
      {
         FUNCTION_TARGETS(FunctionB, stdFunctionA);
         FAIL("FUNCTION_TARGETS() did not throw Anomaly");
      }
      catch (const Anomaly& anomaly)
      {
#ifdef __linux__
         REGEX_MATCHES(R"(
  Failed: FUNCTION_TARGETS\(FunctionB, stdFunctionA\)
Expected: 1
  Actual: <non-empty std::function>
 Because: IS_NOT_NULL\(stdFunction.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
Expected: not nullptr
  Actual: nullptr
File.cpp\(1\)
File.cpp\(1\))", anomaly.why);
#elif _WIN32
         REGEX_MATCHES(R"(
  Failed: FUNCTION_TARGETS\(FunctionB, stdFunctionA\)
Expected: 0x\w{16}
  Actual: <non-empty std::function>
 Because: IS_NOT_NULL\(stdFunction.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
Expected: not nullptr
  Actual: nullptr
File.cpp\(1\)
File.cpp\(1\))", anomaly.why);
#endif
      }
   }

   TEST(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_Throws)
   {
      const function<void()> stdFunctionA(FunctionA);
   #ifdef __linux__
      THROWS(FUNCTION_TARGETS(FunctionC, stdFunctionA), Anomaly, R"(
  Failed: FUNCTION_TARGETS(FunctionC, stdFunctionA)
Expected: 1
  Actual: <non-empty std::function>
 Because: ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>()) failed
Expected: 1
  Actual: 1
File.cpp(1)
File.cpp(1))");
   #elif _WIN32
      try
      {
         FUNCTION_TARGETS(FunctionC, stdFunctionA);
         FAIL("FUNCTION_TARGETS() did not throw Anomaly");
      }
      catch (const Anomaly& anomaly)
      {
         REGEX_MATCHES(R"(
  Failed: FUNCTION_TARGETS\(FunctionC, stdFunctionA\)
Expected: 0x\w{16}
  Actual: <non-empty std::function>
 Because: ARE_EQUAL\(expectedStdFunctionTarget, \*stdFunction\.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
Expected: 0x\w{16}
  Actual: 0x\w{16}
File.cpp\(1\)
File.cpp\(1\))", anomaly.why);
      }
   #endif
   }

   TEST(FunctionPointsToSameFunctionAsExpected_DoesNotThrow)
   {
      const function<void()> stdFunctionA(FunctionA);
      FUNCTION_TARGETS(FunctionA, stdFunctionA);
   }

   TEST(FunctionABC_CodeCoverage)
   {
      FunctionA();
      FunctionB(0);
      FunctionC();
   }

   }; RUN(FUNCTION_TARGETSTests)
}
