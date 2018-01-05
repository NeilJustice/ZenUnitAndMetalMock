#include "pch.h"
//#include "ZenUnitTests/Macros/REGEX_MATCHES.h"
//
//namespace ZenUnit
//{
//   TESTS(STD_FUNCTION_TARGETSTests)
//   AFACT(FunctionDoesNotPointToAFunction_Throws_MessagesTestsCase)
//   AFACT(FunctionPointsToFunctionWithDifferentSignatureThanExpected_Throws)
//   AFACT(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_Throws)
//   AFACT(FunctionPointsToSameFunctionAsExpected_DoesNotThrow)
//   AFACT(FunctionABC_CodeCoverage)
//   EVIDENCE
//
//   static void FunctionA() {}
//   static void FunctionB(int) {}
//   static void FunctionC()
//   {
//      // Side effect to ensure FunctionA and FunctionC have different addresses.
//      // Otherwise the Release MSVC linker folds together blank FunctionA and blank FunctionC
//      // resulting in FunctionA and FunctionC having the same address.
//      cout << ' ';
//   }
//
//   TEST(FunctionDoesNotPointToAFunction_Throws_MessagesTestsCase)
//   {
//      const function<void()> emptyStdFunction;
//      const string messageA = "A", messageB = "B";
//      try
//      {
//         STD_FUNCTION_TARGETS(FunctionA, emptyStdFunction, messageA, messageB);
//         FAILTEST("STD_FUNCTION_TARGETS() did not throw Anomaly");
//      }
//      catch (const Anomaly& anomaly)
//      {
//         string expectedPattern;
//#if defined __linux__
//         expectedPattern = "1";
//#elif defined _WIN64
//         expectedPattern = "0x\\w{16}";
//#elif defined _WIN32
//         expectedPattern = "0x\\w{8}";
//#endif
//         REGEX_MATCHES(R"(
//  Failed: STD_FUNCTION_TARGETS\(FunctionA, emptyStdFunction, messageA, messageB\)
//Expected: )" + expectedPattern + R"(
//  Actual: <empty std::function>
// Because: IS_TRUE\(stdFunction\) failed
//Expected: true
//  Actual: false
// Message: "A", "B"
//File.cpp\(1\)
//File.cpp\(1\))", anomaly.why);
//      }
//   }
//
//   TEST(FunctionPointsToFunctionWithDifferentSignatureThanExpected_Throws)
//   {
//      const function<void()> stdFunctionA(FunctionA);
//      try
//      {
//         STD_FUNCTION_TARGETS(FunctionB, stdFunctionA);
//         FAILTEST("STD_FUNCTION_TARGETS() did not throw Anomaly");
//      }
//      catch (const Anomaly& anomaly)
//      {
//         string expectedPattern;
//#if defined __linux__
//         expectedPattern = "1";
//#elif defined _WIN64
//         expectedPattern = "0x\\w{16}";
//#elif defined _WIN32
//         expectedPattern = "0x\\w{8}";
//#endif
//         REGEX_MATCHES(R"(
//  Failed: STD_FUNCTION_TARGETS\(FunctionB, stdFunctionA\)
//Expected: )" + expectedPattern + R"(
//  Actual: <non-empty std::function>
// Because: IS_NOT_NULL\(stdFunction.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
//Expected: not nullptr
//  Actual: nullptr
//File.cpp\(1\)
//File.cpp\(1\))", anomaly.why);
//      }
//   }
//
//   TEST(FunctionPointsToFunctionWithSameSignatureButDifferentFunctionThanExpected_Throws)
//   {
//      const function<void()> stdFunctionA(FunctionA);
//   #if defined __linux__
//      THROWS(STD_FUNCTION_TARGETS(FunctionC, stdFunctionA), Anomaly, R"(
//  Failed: STD_FUNCTION_TARGETS(FunctionC, stdFunctionA)
//Expected: 1
//  Actual: <non-empty std::function>
// Because: ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>()) failed
//Expected: 1
//  Actual: 1
//File.cpp(1)
//File.cpp(1))");
//   #elif _WIN32
//      try
//      {
//         STD_FUNCTION_TARGETS(FunctionC, stdFunctionA);
//         FAILTEST("STD_FUNCTION_TARGETS() did not throw Anomaly");
//      }
//      catch (const Anomaly& anomaly)
//      {
//#if defined _WIN64
//         REGEX_MATCHES(R"(
//  Failed: STD_FUNCTION_TARGETS\(FunctionC, stdFunctionA\)
//Expected: 0x\w{16}
//  Actual: <non-empty std::function>
// Because: ARE_EQUAL\(expectedStdFunctionTarget, \*stdFunction\.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
//Expected: 0x\w{16}
//  Actual: 0x\w{16}
//File.cpp\(1\)
//File.cpp\(1\))", anomaly.why);
//#elif _WIN32
//         REGEX_MATCHES(R"(
//  Failed: STD_FUNCTION_TARGETS\(FunctionC, stdFunctionA\)
//Expected: 0x\w{8}
//  Actual: <non-empty std::function>
// Because: ARE_EQUAL\(expectedStdFunctionTarget, \*stdFunction\.template target<ExpectedStdFunctionTargetType\*>\(\)\) failed
//Expected: 0x\w{8}
//  Actual: 0x\w{8}
//File.cpp\(1\)
//File.cpp\(1\))", anomaly.why);
//#endif
//      }
//   #endif
//   }
//
//   TEST(FunctionPointsToSameFunctionAsExpected_DoesNotThrow)
//   {
//      const function<void()> stdFunctionA(FunctionA);
//      STD_FUNCTION_TARGETS(FunctionA, stdFunctionA);
//   }
//
//   TEST(FunctionABC_CodeCoverage)
//   {
//      FunctionA();
//      FunctionB(0);
//      FunctionC();
//   }
//
//   }; RUNTESTS(STD_FUNCTION_TARGETSTests)
//}
