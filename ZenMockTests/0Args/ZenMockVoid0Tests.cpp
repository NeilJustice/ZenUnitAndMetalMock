#include "pch.h"
#include "ZenMockTests/0Args/ZenMock0Tester.h"

void Void0Function() {}

namespace ZenMock
{
   struct Void0Functions
   {
      virtual void Virtual() {}
      virtual void VirtualConst() const {}
      void NonVirtual() {}
      void NonVirtualConst() const {}
      virtual ~Void0Functions() = default;
   };

   struct Void0FunctionsMock : public Zen::Mock<Void0Functions>
   {
      ZENMOCK_VOID0(Virtual)
      ZENMOCK_VOID0_CONST(VirtualConst)
      ZENMOCK_VOID0_NONVIRTUAL(NonVirtual)
      ZENMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualConst)
   };

   void Void0Function() {}

   struct StaticVoid0Functions
   {
      static void StaticVoid0Function() {}
      static void Void0Function() {}
   };

   TESTS(ZenMockVoid0Tests)
   // ZeroArgumentMocker Tests
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(ZenMockedFunction_NotExpected_Throws)
   AFACT(ZenMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   AFACT(ThrowException_ThenZenMockedFunction_ThrowsTheException)
   // Void0 Tests
   AFACT(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   EVIDENCE

   ZENMOCK_VOID0_FREE(Void0Function)
   // ZENMOCK_VOID0_NAMESPACED_FREE
   ZENMOCK_VOID0_STATIC(ZenMock, Void0Function, _namespace)
   ZENMOCK_VOID0_STATIC(ZenMock::StaticVoid0Functions, StaticVoid0Function)
   ZENMOCK_VOID0_STATIC(ZenMock::StaticVoid0Functions, Void0Function, _static)

   const string ExpectedVirtualFunctionSignature =
      "virtual void ZenMock::Void0Functions::Virtual()";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void ZenMock::Void0Functions::VirtualConst() const";
   const string ExpectedNonVirtualFunctionSignature =
      "void ZenMock::Void0Functions::NonVirtual()";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void ZenMock::Void0Functions::NonVirtualConst() const";
   const string FreeFunctionSignature =
      "void ::Void0Function()";
   const string ExpectedNamespacedFunctionSignature =
      "void ZenMock::Void0Function()";
   const string StaticFunctionSignature =
      "void ZenMock::StaticVoid0Functions::StaticVoid0Function()";
   const string ExpectedStaticFunctionNameClashSignature =
      "void ZenMock::StaticVoid0Functions::Void0Function()";

   Void0FunctionsMock _mock;

   unique_ptr<ZenMock0Tester<
      Void0FunctionsMock,
      decltype(Void0Function_ZenMockObject),
      decltype(Void0Function_ZenMockObject_namespace),
      decltype(StaticVoid0Function_ZenMockObject),
      decltype(Void0Function_ZenMockObject_static)>> _zenMock0Tester;

   STARTUP
   {
      _zenMock0Tester = make_unique<ZenMock0Tester<
         Void0FunctionsMock,
         decltype(Void0Function_ZenMockObject),
         decltype(Void0Function_ZenMockObject_namespace),
         decltype(StaticVoid0Function_ZenMockObject),
         decltype(Void0Function_ZenMockObject_static)>>(_mock,
            ExpectedVirtualFunctionSignature,
            ExpectedVirtualConstFunctionSignature,
            ExpectedNonVirtualFunctionSignature,
            ExpectedNonVirtualConstFunctionSignature,
            Void0Function_ZenMockObject,
            FreeFunctionSignature,
            Void0Function_ZenMockObject_namespace,
            ExpectedNamespacedFunctionSignature,
            StaticVoid0Function_ZenMockObject,
            StaticFunctionSignature,
            Void0Function_ZenMockObject_static,
            ExpectedStaticFunctionNameClashSignature);
   }

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_Throws();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(ZenMockedFunction_NotExpected_Throws)
   {
      _zenMock0Tester->ZenMockedFunction_NotExpected_Throws();
   }

   TEST(ZenMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   {
      _zenMock0Tester->ZenMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow();
   }

   TEST(ThrowException_ThenZenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->ThrowException_ThenZenMockedFunction_ThrowsTheException();
   }

   // Void0 Tests

   TEST(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   {
      const auto test = [](auto& zenMockObject)
      {
         zenMockObject.Expect();
         zenMockObject.Expect();
         //
         zenMockObject.ZenMockIt();
         //
         zenMockObject.CalledOnce();
      };
      test(_mock.VirtualMock);
      test(_mock.VirtualConstMock);
      test(_mock.NonVirtualMock);
      test(_mock.NonVirtualConstMock);

      test(Void0Function_ZenMockObject);
      test(Void0Function_ZenMockObject_namespace);
      test(StaticVoid0Function_ZenMockObject);
      test(Void0Function_ZenMockObject_static);
   }

   RUN_TESTS(ZenMockVoid0Tests)
}
