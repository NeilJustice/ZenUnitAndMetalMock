#include "pch.h"
#include "ZenMock0Tester.h"

void Void0() {}

namespace ZenMock
{
   void Void0() {}
   struct FunctionPointerTesting
   {
      static void Void0() {}
      static void Static() {}
   };

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
      ZENMOCK_VOID0_CONST_NONVIRTUAL(NonVirtualConst)
   };

   TESTS(ZenMock_Void0Tests)
   // ZeroArgMocker Tests
   SPEC(Expect_CalledTwice_Throws)
   SPEC(ExpectAndThrow_CalledTwice_Throws)
   SPEC(FunctionNotCalled_AssertCalledNTimesWithN0_Throws)
   SPEC(FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows)
   SPEC(Function_NotExpected_Throws)
   SPEC(Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow)
   SPEC(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   SPECEND

   Void0FunctionsMock _mock;
   ZENMOCK_VOID0_FREE(Void0)
   ZENMOCK_VOID0_STATIC(ZenMock, Void0, _namespace)
   ZENMOCK_VOID0_STATIC(ZenMock::FunctionPointerTesting, Void0, _static)
   ZENMOCK_VOID0_STATIC(ZenMock::FunctionPointerTesting, Static)
   unique_ptr<ZenMock0Tester<
      Void0FunctionsMock,
      decltype(Void0_ZenMock),
      decltype(Void0_ZenMock_namespace),
      decltype(Void0_ZenMock_static),
      decltype(Static_ZenMock)>> _zenMock0Tester;

   const string VirtualSignature =
      "virtual void ZenMock::Void0Functions::Virtual()";
   const string VirtualConstSignature =
      "virtual void ZenMock::Void0Functions::VirtualConst() const";
   const string NonVirtualSignature =
      "void ZenMock::Void0Functions::NonVirtual()";
   const string NonVirtualConstSignature =
      "void ZenMock::Void0Functions::NonVirtualConst() const";
   const string FreeSignature =
      "void ::Void0()";
   const string NamespaceSignature =
      "void ZenMock::Void0()";
   const string StaticNameClashSignature =
      "void ZenMock::FunctionPointerTesting::Void0()";
   const string StaticUniqueSignature =
      "void ZenMock::FunctionPointerTesting::Static()";

   STARTUP
   {
      _zenMock0Tester = make_unique<ZenMock0Tester<
         Void0FunctionsMock,
         decltype(Void0_ZenMock),
         decltype(Void0_ZenMock_namespace),
         decltype(Void0_ZenMock_static),
         decltype(Static_ZenMock)>>(
            _mock,
            VirtualSignature,
            VirtualConstSignature,
            NonVirtualSignature,
            NonVirtualConstSignature,

            Void0_ZenMock,
            FreeSignature,

            Void0_ZenMock_namespace,
            NamespaceSignature,

            Void0_ZenMock_static,
            StaticNameClashSignature,

            Static_ZenMock,
            StaticUniqueSignature);
   }

   TEST(Expect_CalledTwice_Throws)
   {
      _zenMock0Tester->Expect_CalledTwice_Throws();
   }

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock0Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(FunctionNotCalled_AssertCalledNTimesWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_AssertCalledNTimesWithN0_Throws();
   }

   TEST(FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows();
   }

   TEST(Function_NotExpected_Throws)
   {
      _zenMock0Tester->Function_NotExpected_Throws();
   }

   TEST(Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow)
   {
      _zenMock0Tester->Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow();
   }

   TEST(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->ExpectAndThrow_ThenMockedFunction_ThrowsTheException();
   }

   }; RUN(ZenMock_Void0Tests)
}
