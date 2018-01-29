#include "pch.h"
#include "ZenMock1Tester.h"

// Windows-only tests until Travis CI no longer runs out of memory
#ifdef _WIN32

void Void1Function(int) {}

namespace ZenMock
{
   struct Void1Functions
   {
      virtual void VirtualFunction(int) {}
      virtual void VirtualConstFunction(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualConstFunction(int) const {}
      virtual ~Void1Functions() = default;
   };

   struct Void1FunctionsMock : public Zen::Mock<Void1Functions>
   {
      ZENMOCK_VOID1(VirtualFunction, int)
      ZENMOCK_VOID1_CONST(VirtualConstFunction, int)
      ZENMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      ZENMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualConstFunction, int)
   };

   void Void1Function(int) {}

   struct Void1StaticFunctions
   {
      static void StaticVoid1Function(int) {}
      static void OverloadedStaticVoid1Function(float) {}
      static void OverloadedStaticVoid1Function(double) {}
   };

   TESTS(ZenMock_Void1Tests)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   EVIDENCE

   const string ExpectedVirtualFunctionSignature =
      "virtual void ZenMock::Void1Functions::VirtualFunction(int)";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void ZenMock::Void1Functions::VirtualConstFunction(int) const";
   const string ExpectedNonVirtualFunctionSignature =
      "void ZenMock::Void1Functions::NonVirtualFunction(int)";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void ZenMock::Void1Functions::NonVirtualConstFunction(int) const";
   const string ExpectedFreeFunctionSignature =
      "void ::Void1Function(int)";
   const string ExpectedNamespacedFunctionSignature =
      "void ZenMock::Void1Function(int)";
   const string ExpectedStaticFunctionSignature =
      "void ZenMock::Void1StaticFunctions::StaticFunction(int)";
   const string ExpectedOverloadedStaticFunctionSignatureA =
      "void ZenMock::Void1StaticFunctions::OverloadedStaticFunction(float)";
   const string ExpectedOverloadedStaticFunctionSignatureB =
      "void ZenMock::Void1StaticFunctions::OverloadedStaticFunction(double)";

   Void1FunctionsMock _mock;
   ZENMOCK_VOID1_FREE(Void1Function, int)
   ZENMOCK_VOID1_STATIC(ZenMock, Void1Function, int, _namespace)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, StaticVoid1Function, int)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, OverloadedStaticVoid1Function, float, _float)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, OverloadedStaticVoid1Function, double, _double)

   unique_ptr<ZenMock1Tester<
      Void1FunctionsMock,
      decltype(Void1Function_ZenMock),
      decltype(Void1Function_ZenMock_namespace),
      decltype(StaticVoid1Function_ZenMock),
      decltype(OverloadedStaticVoid1Function_ZenMock_float)>> _zenMock1Tester;

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
         Void1FunctionsMock,
         decltype(Void1Function_ZenMock),
         decltype(Void1Function_ZenMock_namespace),
         decltype(StaticVoid1Function_ZenMock),
         decltype(OverloadedStaticVoid1Function_ZenMock_float)>>(
            _mock,
            ExpectedVirtualFunctionSignature,
            ExpectedVirtualConstFunctionSignature,
            ExpectedNonVirtualFunctionSignature,
            ExpectedNonVirtualConstFunctionSignature,

            Void1Function_ZenMock,
            ExpectedFreeFunctionSignature,

            Void1Function_ZenMock_namespace,
            ExpectedNamespacedFunctionSignature,

            StaticVoid1Function_ZenMock,
            ExpectedStaticFunctionSignature,

            OverloadedStaticVoid1Function_ZenMock_float,
            ExpectedOverloadedStaticFunctionSignatureA);
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& zenMockObject)
      {
         zenMockObject.Expect();
         zenMockObject.ZenMockIt(0);
         zenMockObject.Expect();
         zenMockObject.CalledOnceWith(0);
      };
      test(_mock.VirtualFunctionMock);
      test(_mock.VirtualConstFunctionMock);
      test(_mock.NonVirtualFunctionMock);
      test(_mock.NonVirtualConstFunctionMock);
      test(Void1Function_ZenMock);
      test(Void1Function_ZenMock_namespace);
      test(StaticVoid1Function_ZenMock);
      test(OverloadedStaticVoid1Function_ZenMock_float);
   }

   }; RUN_TESTS(ZenMock_Void1Tests)
}


#include "pch.h"
#include "ZenMock1Tester.h"

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

   TESTS(ZenMock_NonVoid1Tests)
   // Expect Tests
   AFACT(MockedFunction_NotExpected_Throws)
   AFACT(MockedFunction_Expected_DoesNotThrow)
   AFACT(Throw_CalledTwice_Throws)
   AFACT(Throw_ThenFunction_ThrowsTheException)
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
   FACTS(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws)
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
      ZENMOCK_NONVOID1_STATIC(int, ZenMock, NonVoid1, int, _namespace)
      ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, NonVoid1, int, _static)
      ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, Static, int)
      unique_ptr<ZenMock1Tester<
      NonVoid1FunctionsMock,
      decltype(NonVoid1_ZenMock),
      decltype(NonVoid1_ZenMock_namespace),
      decltype(Static_ZenMock),
      decltype(NonVoid1_ZenMock_static)>> _zenMock1Tester;

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
      NonVoid1FunctionsMock,
      decltype(NonVoid1_ZenMock),
      decltype(NonVoid1_ZenMock_namespace),
      decltype(Static_ZenMock),
      decltype(NonVoid1_ZenMock_static)>>(
         mock,
         VirtualSignature,
         VirtualConstSignature,
         NonVirtualSignature,
         NonVirtualConstSignature,
         NonVoid1_ZenMock,
         FreeSignature,
         NonVoid1_ZenMock_namespace,
         NamespaceSignature,
         Static_ZenMock,
         StaticUniqueSignature,
         NonVoid1_ZenMock_static,
         StaticNameClashSignature);
   }

   // Expect Tests

   TEST(MockedFunction_NotExpected_Throws)
   {
      _zenMock1Tester->MockedFunction_NotExpected_Throws();
   }

   TEST(MockedFunction_Expected_DoesNotThrow)
   {
      _zenMock1Tester->MockedFunction_Expected_DoesNotThrow();
   }

   TEST(Throw_CalledTwice_Throws)
   {
      _zenMock1Tester->Throw_CalledTwice_Throws();
   }

   TEST(Throw_ThenFunction_ThrowsTheException)
   {
      _zenMock1Tester->Throw_ThenFunction_ThrowsTheException();
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

      test(NonVoid1_ZenMock, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&] { return ZENMOCK_BIND1(Static_ZenMock)(0); });
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

      test(NonVoid1_ZenMock, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&] { return ZENMOCK_BIND1(Static_ZenMock)(0); });
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

      test(NonVoid1_ZenMock, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&] { return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&] { return ZENMOCK_BIND1(Static_ZenMock)(0); });
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
      size_t(1), size_t(0), R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0)",
      size_t(1), size_t(2), R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 2)",
      size_t(2), size_t(0), R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 2
  Actual: 0)",
      size_t(2), size_t(1), R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 2
  Actual: 1)",
      size_t(2), size_t(3), R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0, ZenMock::OneArgumentCall:
Argument: 0}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 2
  Actual: 3)")
   {
      _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         expectedCallsSize, numberOfCalls, expectedExceptionWhatPrefix);
   }

   TEST3X3(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws,
      size_t expectedCallsSize, size_t mismatchingCallIndex, const string& expectedExceptionWhatPrefix,
      size_t(1), size_t(0),
      R"(
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 10}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 20}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=0")",
      size_t(2), size_t(0),
      R"(
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 10, ZenMock::OneArgumentCall:
Argument: 10}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 20, ZenMock::OneArgumentCall:
Argument: 10}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=0")",
      size_t(2), size_t(1),
      R"(
Expected: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 10, ZenMock::OneArgumentCall:
Argument: 10}
  Actual: vector<ZenMock::OneArgumentCallRef<int>>: {ZenMock::OneArgumentCall:
Argument: 10, ZenMock::OneArgumentCall:
Argument: 20}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=1")")
   {
      _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         expectedCallsSize, mismatchingCallIndex, expectedExceptionWhatPrefix);
   }

   TEST1X1(CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow,
      size_t expectedCallsSize,
      size_t(1),
      size_t(2))
   {
      _zenMock1Tester->CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(expectedCallsSize);
   }

}; RUN_TESTS(ZenMock_NonVoid1Tests)

}

#endif
