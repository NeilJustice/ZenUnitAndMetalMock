#include "pch.h"
#include "ZenMock1Tester.h"

int NonVoid1(int) { return 0; }

namespace ZenMock
{
   int NonVoid1(int) { return 0; }
   struct FunctionPointerTesting
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
      virtual ~NonVoid1Functions() {}
   };

   struct NonVoid1FunctionsMock : public Zen::Mock<NonVoid1Functions>
   {
      ZENMOCK_NONVOID1(int, Virtual, int)
      ZENMOCK_NONVOID1_CONST(int, VirtualConst, int)
      ZENMOCK_NONVOID1_NONVIRTUAL(int, NonVirtual, int)
      ZENMOCK_NONVOID1_CONST_NONVIRTUAL(int, NonVirtualConst, int)
   };

   TESTS(ZenMock_NonVoid1Tests)
   // Expect Tests
   SPEC(Expect_CalledTwice_Throws)
   SPEC(Function_NotExpected_Throws)
   SPEC(Function_Expected_DoesNotThrow)
   SPEC(ExpectAndThrow_CalledTwice_Throws)
   SPEC(ExpectAndThrow_ThenFunction_ThrowsTheException)
   // Value Return Tests
   SPEC(ExpectAndReturn_CalledTwice_Throws)
   SPEC(ExpectAndReturn_CausesFunctionToReturnValueThereafter)
   SPEC(ExpectAndReturnValues_CalledTwice_Throws)
   SPEC(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   SPEC(ExpectAndReturnValuesVector_CalledTwice_Throws)
   SPEC(ExpectAndReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   // Assertion Tests
   SPECX(AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws)
   SPEC(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   SPEC(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   SPEC(AssertCalledNTimesWith_N0_Throws)
   SPECX(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws)
   SPECX(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws)
   SPECX(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow)
   SPEC(AssertCalls_EmptyCalls_Throws)
   SPECX(AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws)
   SPECX(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws)
   SPECX(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow)
   SPECEND

   NonVoid1FunctionsMock mock;
   ZENMOCK_NONVOID1_GLOBAL(int, NonVoid1, int)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock, NonVoid1, int, _namespace)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::FunctionPointerTesting, NonVoid1, int, _static)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::FunctionPointerTesting, Static, int)
   unique_ptr<ZenMock1Tester<
      NonVoid1FunctionsMock,
      decltype(NonVoid1_ZenMock),
      decltype(NonVoid1_ZenMock_namespace),
      decltype(NonVoid1_ZenMock_static),
      decltype(Static_ZenMock)>> _zenMock1Tester;

   const string VirtualSignature =
      "virtual int ZenMock::NonVoid1Functions::Virtual(int)";
   const string VirtualConstSignature =
      "virtual int ZenMock::NonVoid1Functions::VirtualConst(int) const";
   const string NonVirtualSignature =
      "int ZenMock::NonVoid1Functions::NonVirtual(int)";
   const string NonVirtualConstSignature =
      "int ZenMock::NonVoid1Functions::NonVirtualConst(int) const";
   const string GlobalSignature =
      "int ::NonVoid1(int)";
   const string NamespaceSignature =
      "int ZenMock::NonVoid1(int)";
   const string StaticNameClashSignature =
      "int ZenMock::FunctionPointerTesting::NonVoid1(int)";
   const string StaticUniqueSignature =
      "int ZenMock::FunctionPointerTesting::Static(int)";

   STARTUP
   {
      _zenMock1Tester.reset(new ZenMock1Tester<
         NonVoid1FunctionsMock,
         decltype(NonVoid1_ZenMock),
         decltype(NonVoid1_ZenMock_namespace),
         decltype(NonVoid1_ZenMock_static),
         decltype(Static_ZenMock)>(
            mock,
            VirtualSignature,
            VirtualConstSignature,
            NonVirtualSignature,
            NonVirtualConstSignature,
            NonVoid1_ZenMock,
            GlobalSignature,
            NonVoid1_ZenMock_namespace,
            NamespaceSignature,
            NonVoid1_ZenMock_static,
            StaticNameClashSignature,
            Static_ZenMock,
            StaticUniqueSignature));
   }

   // Expect Tests

   TEST(Expect_CalledTwice_Throws)
   {
      _zenMock1Tester->Expect_CalledTwice_Throws();
   }

   TEST(Function_NotExpected_Throws)
   {
      _zenMock1Tester->Function_NotExpected_Throws();
   }

   TEST(Function_Expected_DoesNotThrow)
   {
      _zenMock1Tester->Function_Expected_DoesNotThrow();
   }

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock1Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(ExpectAndThrow_ThenFunction_ThrowsTheException)
   {
      _zenMock1Tester->ExpectAndThrow_ThenFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(ExpectAndReturn_CalledTwice_Throws)
   {
      const auto test = [](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturn(0);
         THROWS(zenMockObject.ExpectAndReturn(0), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(mock.VirtualMock, VirtualSignature);
      test(mock.VirtualConstMock, VirtualConstSignature);
      test(mock.NonVirtualMock, NonVirtualSignature);
      test(mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid1_ZenMock, GlobalSignature);
      test(NonVoid1_ZenMock_namespace, NamespaceSignature);
      test(NonVoid1_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturn_CausesFunctionToReturnValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturn(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(2, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENBIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENBIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENBIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENBIND1(Static_ZenMock)(0); });
   }

   TEST(ExpectAndReturnValues_CalledTwice_Throws)
   {
      const auto test = [&](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturnValues(0);
         THROWS(zenMockObject.ExpectAndReturnValues(0), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(mock.VirtualMock, VirtualSignature);
      test(mock.VirtualConstMock, VirtualConstSignature);
      test(mock.NonVirtualMock, NonVirtualSignature);
      test(mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid1_ZenMock, GlobalSignature);
      test(NonVoid1_ZenMock_namespace, NamespaceSignature);
      test(NonVoid1_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENBIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENBIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENBIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENBIND1(Static_ZenMock)(0); });
   }

   TEST(ExpectAndReturnValuesVector_CalledTwice_Throws)
   {
      const auto test = [](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturnValues({0});
         THROWS(zenMockObject.ExpectAndReturnValues({0}), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(mock.VirtualMock, VirtualSignature);
      test(mock.VirtualConstMock, VirtualConstSignature);
      test(mock.NonVirtualMock, NonVirtualSignature);
      test(mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid1_ZenMock, GlobalSignature);
      test(NonVoid1_ZenMock_namespace, NamespaceSignature);
      test(NonVoid1_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         const vector<int> values = { 1, 2 };
         zenMockObject.ExpectAndReturnValues(values);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENBIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENBIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENBIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENBIND1(Static_ZenMock)(0); });
   }

   // Assertion Tests

   TEST1X1(AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws, size_t numberOfCalls, 0ull, 2ull, 3ull)
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(numberOfCalls);
   }

   TEST(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws();
   }

   TEST(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow();
   }

   TEST(AssertCalledNTimesWith_N0_Throws)
   {
      _zenMock1Tester->AssertCalledNTimesWith_N0_Throws();
   }

   TEST2X2(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws,
      size_t n, size_t numberOfCalls,
      1ull, 0ull,
      1ull, 2ull,
      2ull, 0ull,
      2ull, 1ull,
      2ull, 3ull)
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws(n, numberOfCalls);
   }

   TEST2X2(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws,
      size_t n, size_t mismatchingCallIndex,
      1ull, 0ull,
      2ull, 0ull,
      2ull, 1ull)
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws(
         n, mismatchingCallIndex);
   }

   TEST1X1(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow,
      size_t n,
      1ull,
      2ull)
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow(n);
   }

   TEST(AssertCalls_EmptyCalls_Throws)
   {
      _zenMock1Tester->AssertCalls_EmptyCalls_Throws();
   }

   TEST2X2(AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws,
      size_t expectedCallsSize, size_t numberOfCalls,
      1ull, 0ull,
      1ull, 2ull,
      2ull, 0ull,
      2ull, 1ull,
      2ull, 3ull)
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         expectedCallsSize, numberOfCalls);
   }

   TEST2X2(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws,
      size_t expectedCallsSize, size_t mismatchingCallIndex,
      1ull, 0ull,
      2ull, 0ull,
      2ull, 1ull)
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         expectedCallsSize, mismatchingCallIndex);
   }

   TEST1X1(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow,
      size_t expectedCallsSize,
      1ull,
      2ull)
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(expectedCallsSize);
   }

   }; RUN(ZenMock_NonVoid1Tests)
}
