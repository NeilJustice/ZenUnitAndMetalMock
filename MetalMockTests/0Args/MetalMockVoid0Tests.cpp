#include "pch.h"
#include "MetalMockTests/0Args/MetalMock0Tester.h"

void Void0Function() {}

namespace MetalMock
{
   struct Void0Functions
   {
      virtual void Virtual() {}
      virtual void VirtualConst() const {}
      void NonVirtual() {}
      void NonVirtualConst() const {}
      virtual ~Void0Functions() = default;
   };

   struct Void0FunctionsMock : public Metal::Mock<Void0Functions>
   {
      METALMOCK_VOID0(Virtual)
      METALMOCK_VOID0_CONST(VirtualConst)
      METALMOCK_VOID0_NONVIRTUAL(NonVirtual)
      METALMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualConst)
   };

   void Void0Function() {}

   struct StaticVoid0Functions
   {
      static void StaticVoid0Function() {}
      static void Void0Function() {}
   };

   TESTS(MetalMockVoid0Tests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::Void0Function();
      MetalMock::Void0Function();

      MetalMock::Void0Functions void0Functions;
      void0Functions.Virtual();
      void0Functions.VirtualConst();
      void0Functions.NonVirtual();
      void0Functions.NonVirtualConst();

      MetalMock::Void0Function();

      MetalMock::StaticVoid0Functions::StaticVoid0Function();
      MetalMock::StaticVoid0Functions::Void0Function();
   }

   RUN_TESTS(MetalMockVoid0Tests_CodeCoverage)

   TESTS(MetalMockVoid0Tests)
   // ZeroArgumentMetalMocker Tests
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(MetalMockedFunction_NotExpected_Throws)
   AFACT(MetalMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   AFACT(ThrowException_ThenMetalMockedFunction_ThrowsTheException)
   // Void0 Tests
   AFACT(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   EVIDENCE

   METALMOCK_VOID0_FREE(Void0Function)
   // METALMOCK_VOID0_NAMESPACED_FREE
   METALMOCK_VOID0_STATIC(MetalMock, Void0Function, _namespace)
   METALMOCK_VOID0_STATIC(MetalMock::StaticVoid0Functions, StaticVoid0Function)
   METALMOCK_VOID0_STATIC(MetalMock::StaticVoid0Functions, Void0Function, _static)

   const string ExpectedVirtualFunctionSignature =
      "virtual void MetalMock::Void0Functions::Virtual()";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void MetalMock::Void0Functions::VirtualConst() const";
   const string ExpectedNonVirtualFunctionSignature =
      "void MetalMock::Void0Functions::NonVirtual()";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void MetalMock::Void0Functions::NonVirtualConst() const";
   const string FreeFunctionSignature =
      "void ::Void0Function()";
   const string ExpectedNamespacedFunctionSignature =
      "void MetalMock::Void0Function()";
   const string StaticFunctionSignature =
      "void MetalMock::StaticVoid0Functions::StaticVoid0Function()";
   const string ExpectedStaticFunctionNameClashSignature =
      "void MetalMock::StaticVoid0Functions::Void0Function()";

   Void0FunctionsMock _mock;

   unique_ptr<MetalMock0Tester<
      Void0FunctionsMock,
      decltype(Void0FunctionMock),
      decltype(Void0FunctionMock_namespace),
      decltype(StaticVoid0FunctionMock),
      decltype(Void0FunctionMock_static)>> _metalMock0Tester;

   STARTUP
   {
      _metalMock0Tester = make_unique<MetalMock0Tester<
         Void0FunctionsMock,
         decltype(Void0FunctionMock),
         decltype(Void0FunctionMock_namespace),
         decltype(StaticVoid0FunctionMock),
         decltype(Void0FunctionMock_static)>>(_mock,
            ExpectedVirtualFunctionSignature,
            ExpectedVirtualConstFunctionSignature,
            ExpectedNonVirtualFunctionSignature,
            ExpectedNonVirtualConstFunctionSignature,
            Void0FunctionMock,
            FreeFunctionSignature,
            Void0FunctionMock_namespace,
            ExpectedNamespacedFunctionSignature,
            StaticVoid0FunctionMock,
            StaticFunctionSignature,
            Void0FunctionMock_static,
            ExpectedStaticFunctionNameClashSignature);
   }

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   {
      _metalMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_Throws();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _metalMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(MetalMockedFunction_NotExpected_Throws)
   {
      _metalMock0Tester->MetalMockedFunction_NotExpected_Throws();
   }

   TEST(MetalMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow)
   {
      _metalMock0Tester->MetalMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow();
   }

   TEST(ThrowException_ThenMetalMockedFunction_ThrowsTheException)
   {
      _metalMock0Tester->ThrowException_ThenMetalMockedFunction_ThrowsTheException();
   }

   // Void0 Tests

   TEST(Expect_MakesFunctionCallNotThrow_DoesNotThrowIfExpectCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.Expect();
         //
         metalMockObject.MetalMockIt();
         //
         metalMockObject.CalledOnce();
      };
      test(_mock.VirtualMock);
      test(_mock.VirtualConstMock);
      test(_mock.NonVirtualMock);
      test(_mock.NonVirtualConstMock);

      test(Void0FunctionMock);
      test(Void0FunctionMock_namespace);
      test(StaticVoid0FunctionMock);
      test(Void0FunctionMock_static);
   }

   RUN_TESTS(MetalMockVoid0Tests)
}
