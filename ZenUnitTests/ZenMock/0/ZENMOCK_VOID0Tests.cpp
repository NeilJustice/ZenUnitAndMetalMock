#include "pch.h"
#include "ZenMock0Tester.h"

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

   TESTS(ZenMock_Void0Tests)
   // ZeroArgumentMocker Tests
   AFACT(ExpectAndThrow_CalledTwice_Throws)
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(Function_NotExpected_Throws)
   AFACT(Function_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   AFACT(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   // Void0 Tests
   AFACT(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   EVIDENCE

   ZENMOCK_VOID0_FREE(Void0Function)
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
   const string ExpectedFreeFunctionSignature =
      "void ::Void0Function()";
   const string ExpectedNamespacedFunctionSignature =
      "void ZenMock::Void0Function()";
   const string ExpectedStaticFunctionSignature =
      "void ZenMock::StaticVoid0Functions::StaticVoid0Function()";
   const string ExpectedStaticFunctionNameClashSignature =
      "void ZenMock::StaticVoid0Functions::Void0Function()";

   Void0FunctionsMock _mock;

   unique_ptr<ZenMock0Tester<
      Void0FunctionsMock,
      decltype(Void0Function_ZenMock),
      decltype(Void0Function_ZenMock_namespace),
      decltype(StaticVoid0Function_ZenMock),
      decltype(Void0Function_ZenMock_static)>> _zenMock0Tester;

   STARTUP
   {
      _zenMock0Tester = make_unique<ZenMock0Tester<
         Void0FunctionsMock,
         decltype(Void0Function_ZenMock),
         decltype(Void0Function_ZenMock_namespace),
         decltype(StaticVoid0Function_ZenMock),
         decltype(Void0Function_ZenMock_static)>>(_mock,
            ExpectedVirtualFunctionSignature,
            ExpectedVirtualConstFunctionSignature,
            ExpectedNonVirtualFunctionSignature,
            ExpectedNonVirtualConstFunctionSignature,
            Void0Function_ZenMock,
            ExpectedFreeFunctionSignature,
            Void0Function_ZenMock_namespace,
            ExpectedNamespacedFunctionSignature,
            StaticVoid0Function_ZenMock,
            ExpectedStaticFunctionSignature,
            Void0Function_ZenMock_static,
            ExpectedStaticFunctionNameClashSignature);
   }

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock0Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_Throws();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(Function_NotExpected_Throws)
   {
      _zenMock0Tester->Function_NotExpected_Throws();
   }

   TEST(Function_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   {
      _zenMock0Tester->Function_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow();
   }

   TEST(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->ExpectAndThrow_ThenMockedFunction_ThrowsTheException();
   }

   // Void0 Tests

   TEST(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   {
      //const auto test = [](auto& zenMockObject)
      //{
      //   zenMockObject.Expect();
      //   zenMockObject.Expect();
      //};
      //test(_mock.VirtualMock);
      //test(_mock.VirtualConstMock);
      //test(_mock.NonVirtualMock);
      //test(_mock.NonVirtualConstMock);
      //test(Void0Function_ZenMock);
      //test(Void0Function_ZenMock_namespace);
      //test(StaticVoid0Function_ZenMock);
      //test(Void0Function_ZenMock_static);
   }

   }; RUNTESTS(ZenMock_Void0Tests)
}
