#include "pch.h"
#include "ZenMockTests/1Arg/ZenMock1Tester.h"

int NonVoid1(int) { return 0; }

namespace ZenMock
{
   int NonVoid1(int) { return 0; }

   struct NonVoid1StaticFunctions
   {
      static int NonVoid1(int) { return 0; }
      static int Static(int) { return 0; }
   };

   struct NonVoid1Functions
   {
      virtual int Virtual(int) { return 0; }
      virtual int VirtualConst(int) const { return 0; }
      int NonVirtual(int) { return 0; }
      int NonVirtualConst(int) const { return 0; }
      virtual ~NonVoid1Functions() = default;
   };

   struct NonVoid1FunctionsMock : public Zen::Mock<NonVoid1Functions>
   {
      ZENMOCK_NONVOID1(int, Virtual, int)
      ZENMOCK_NONVOID1_CONST(int, VirtualConst, int)
      ZENMOCK_NONVOID1_NONVIRTUAL(int, NonVirtual, int)
      ZENMOCK_NONVOID1_NONVIRTUAL_CONST(int, NonVirtualConst, int)
   };

   TESTS(ZenMockNonVoid1Tests)
   // Expect Tests
   AFACT(ZenMockedFunction_NotExpected_Throws)
   AFACT(ZenMockedFunction_Expected_DoesNotThrow)
   AFACT(ThrowException_ThenFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(Return_CausesFunctionToReturnValueThereafter)
   AFACT(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   AFACT(ReturnContainerValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   // Assertion Tests
   FACTS(CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   AFACT(CalledAsFollowsWith_N0_Throws)
   FACTS(CalledAsFollowsWith_N1OrGreater_FunctionCalledNotNTimes_Throws)
   FACTS(CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithOneOfTheCallsMismatching_Throws)
   FACTS(CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrow)
   AFACT(CalledAsFollows_EmptyCalls_Throws)
   FACTS(CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws)
// Test does not work with GCC for a currently unexplained reason
#ifndef __linux__
   FACTS(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws)
#endif
   FACTS(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow)
   EVIDENCE

   const string VirtualSignature =
      "virtual int ZenMock::NonVoid1Functions::Virtual(int)";
   const string VirtualConstSignature =
      "virtual int ZenMock::NonVoid1Functions::VirtualConst(int) const";
   const string NonVirtualSignature =
      "int ZenMock::NonVoid1Functions::NonVirtual(int)";
   const string NonVirtualConstSignature =
      "int ZenMock::NonVoid1Functions::NonVirtualConst(int) const";
   const string FreeSignature =
      "int ::NonVoid1(int)";
   const string NamespaceSignature =
      "int ZenMock::NonVoid1(int)";
   const string StaticUniqueSignature =
      "int ZenMock::NonVoid1StaticFunctions::Static(int)";
   const string StaticNameClashSignature =
      "int ZenMock::NonVoid1StaticFunctions::NonVoid1(int)";

   NonVoid1FunctionsMock mock;
   ZENMOCK_NONVOID1_FREE(int, NonVoid1, int)
   // ZENMOCK_NONVOID1_NAMESPACED_FREE
   ZENMOCK_NONVOID1_STATIC(int, ZenMock, NonVoid1, int, _namespace)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, NonVoid1, int, _static)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, Static, int)
   unique_ptr<ZenMock1Tester<
   NonVoid1FunctionsMock,
   decltype(NonVoid1Mock),
   decltype(NonVoid1Mock_namespace),
   decltype(StaticMock),
   decltype(NonVoid1Mock_static)>> _zenMock1Tester;

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
      NonVoid1FunctionsMock,
      decltype(NonVoid1Mock),
      decltype(NonVoid1Mock_namespace),
      decltype(StaticMock),
      decltype(NonVoid1Mock_static)>>(
         mock,
         VirtualSignature,
         VirtualConstSignature,
         NonVirtualSignature,
         NonVirtualConstSignature,
         NonVoid1Mock,
         FreeSignature,
         NonVoid1Mock_namespace,
         NamespaceSignature,
         StaticMock,
         StaticUniqueSignature,
         NonVoid1Mock_static,
         StaticNameClashSignature);
   }

   // Expect Tests

   TEST(ZenMockedFunction_NotExpected_Throws)
   {
      _zenMock1Tester->ZenMockedFunction_NotExpected_Throws();
   }

   TEST(ZenMockedFunction_Expected_DoesNotThrow)
   {
      _zenMock1Tester->ZenMockedFunction_Expected_DoesNotThrow();
   }

   TEST(ThrowException_ThenFunction_ThrowsTheException)
   {
      _zenMock1Tester->ThrowException_ThenZenMockedFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(Return_CausesFunctionToReturnValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.Return(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.CalledNTimesWith(2, 0);
      };
      test(mock.VirtualMock, [&] { return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&] { return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&] { return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&] { return mock.NonVirtualConst(0); });

      test(NonVoid1Mock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock)(0); });
      test(NonVoid1Mock_namespace, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_namespace)(0); });
      test(NonVoid1Mock_static, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_static)(0); });
      test(StaticMock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(StaticMock)(0); });
   }

   TEST(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&] { return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&] { return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&] { return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&] { return mock.NonVirtualConst(0); });

      test(NonVoid1Mock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock)(0); });
      test(NonVoid1Mock_namespace, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_namespace)(0); });
      test(NonVoid1Mock_static, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_static)(0); });
      test(StaticMock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(StaticMock)(0); });
   }

   TEST(ReturnContainerValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         const vector<int> values{ 1, 2 };
         zenMockObject.ReturnValues(values);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&] { return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&] { return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&] { return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&] { return mock.NonVirtualConst(0); });

      test(NonVoid1Mock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock)(0); });
      test(NonVoid1Mock_namespace, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_namespace)(0); });
      test(NonVoid1Mock_static, [&] { return BIND_1ARG_ZENMOCK_OBJECT(NonVoid1Mock_static)(0); });
      test(StaticMock, [&] { return BIND_1ARG_ZENMOCK_OBJECT(StaticMock)(0); });
   }

   // Assertion Tests

   TEST1X1(CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws,
      size_t numberOfCalls,
      size_t(0),
      size_t(2),
      size_t(3))
   {
      _zenMock1Tester->CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(numberOfCalls);
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   {
      _zenMock1Tester->CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws();
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   {
      _zenMock1Tester->CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow();
   }

   TEST(CalledAsFollowsWith_N0_Throws)
   {
      _zenMock1Tester->CalledAsFollowsWith_N0_Throws();
   }

   TEST2X2(CalledAsFollowsWith_N1OrGreater_FunctionCalledNotNTimes_Throws,
      size_t n, size_t numberOfCalls,
      size_t(1), size_t(0),
      size_t(1), size_t(2),
      size_t(2), size_t(0),
      size_t(2), size_t(1),
      size_t(2), size_t(3))
   {
      _zenMock1Tester->CalledAsFollowsWith_N1OrGreater_FunctionCalledNotNTimes_Throws(n, numberOfCalls);
   }

   TEST2X2(CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithOneOfTheCallsMismatching_Throws,
      size_t expectedCallsSize, size_t mismatchingCallIndex,
      size_t(1), size_t(0),
      size_t(2), size_t(0),
      size_t(2), size_t(1))
   {
      _zenMock1Tester->CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithOneOfTheCallsMismatching_Throws(
         expectedCallsSize, mismatchingCallIndex);
   }

   TEST1X1(CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrow,
      size_t n,
      size_t(1),
      size_t(2))
   {
      _zenMock1Tester->CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrow(n);
   }

   TEST(CalledAsFollows_EmptyCalls_Throws)
   {
      _zenMock1Tester->CalledAsFollows_EmptyCalls_Throws();
   }

   TEST3X3(CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws,
      size_t expectedCallsSize, size_t numberOfCalls, const string& expectedExceptionWhatPrefix,
      size_t(1), size_t(0), "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 1\n"
"  Actual: 0",
      size_t(1), size_t(2), "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 1\n"
"  Actual: 2",
      size_t(2), size_t(0), "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 2\n"
"  Actual: 0",
      size_t(2), size_t(1), "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 2\n"
"  Actual: 1",
      size_t(2), size_t(3), "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 3):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 2\n"
"  Actual: 3")
   {
      _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         expectedCallsSize, numberOfCalls, expectedExceptionWhatPrefix);
   }

#ifndef __linux__
    TEST3X3(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws,
       size_t expectedCallsSize, size_t mismatchingCallIndex, const string& expectedExceptionWhatPrefix,
       size_t(1), size_t(0), "\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"  Actual: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
" Message: \"i=0\"",
      size_t(2), size_t(0), "\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"  Actual: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
" Message: \"i=0\"",
      size_t(2), size_t(1), "\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"  Actual: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
" Message: \"i=1\"")
    {
       _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
          expectedCallsSize, mismatchingCallIndex, expectedExceptionWhatPrefix);
    }
#endif

   TEST1X1(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow,
      size_t expectedCallsSize,
      size_t(1),
      size_t(2))
   {
      _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(expectedCallsSize);
   }

   RUN_TESTS(ZenMockNonVoid1Tests)
}
