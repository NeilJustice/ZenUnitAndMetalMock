#include "pch.h"
#include "MetalMockTests/1Arg/MetalMock1Tester.h"

void Void1Function(int) {}

namespace MetalMock
{
   struct Void1Functions
   {
      virtual void VirtualFunction(int) {}
      virtual void VirtualConstFunction(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualConstFunction(int) const {}
      virtual ~Void1Functions() = default;
   };

   struct Void1FunctionsMock : public Metal::Mock<Void1Functions>
   {
      METALMOCK_VOID1(VirtualFunction, int)
      METALMOCK_VOID1_CONST(VirtualConstFunction, int)
      METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualConstFunction, int)
   };

   void Void1Function(int) {}

   struct Void1StaticFunctions
   {
      static void StaticVoid1Function(int) {}
      static void OverloadedStaticVoid1Function(float) {}
      static void OverloadedStaticVoid1Function(double) {}
   };

   TESTS(MetalMockVoid1Tests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::Void1Function(0);
      MetalMock::Void1Function(0);

      MetalMock::Void1Functions void1Functions;
      void1Functions.VirtualFunction(0);
      void1Functions.VirtualConstFunction(0);
      void1Functions.NonVirtualFunction(0);
      void1Functions.NonVirtualConstFunction(0);

      MetalMock::Void1Function(0);

      MetalMock::Void1StaticFunctions::StaticVoid1Function(0);
      MetalMock::Void1StaticFunctions::OverloadedStaticVoid1Function(0.0f);
      MetalMock::Void1StaticFunctions::OverloadedStaticVoid1Function(0.0);
   }

   RUN_TESTS(MetalMockVoid1Tests_CodeCoverage)

   TESTS(MetalMockVoid1Tests)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   EVIDENCE

   const string ExpectedVirtualFunctionSignature =
      "virtual void MetalMock::Void1Functions::VirtualFunction(int)";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void MetalMock::Void1Functions::VirtualConstFunction(int) const";
   const string ExpectedNonVirtualFunctionSignature =
      "void MetalMock::Void1Functions::NonVirtualFunction(int)";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void MetalMock::Void1Functions::NonVirtualConstFunction(int) const";
   const string FreeFunctionSignature =
      "void Void1Function(int)";
   const string ExpectedNamespacedFunctionSignature =
      "void MetalMock::Void1Function(int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void1StaticFunctions::StaticFunction(int)";
   const string ExpectedOverloadedStaticFunctionSignatureA =
      "void MetalMock::Void1StaticFunctions::OverloadedStaticFunction(float)";
   const string ExpectedOverloadedStaticFunctionSignatureB =
      "void MetalMock::Void1StaticFunctions::OverloadedStaticFunction(double)";

   Void1FunctionsMock _mock;
   METALMOCK_VOID1_FREE(Void1Function, int)
   // METALMOCK_VOID1_NAMESPACED_FREE
   METALMOCK_VOID1_STATIC(MetalMock, Void1Function, int, _namespace)
   METALMOCK_VOID1_STATIC(MetalMock::Void1StaticFunctions, StaticVoid1Function, int)
   METALMOCK_VOID1_STATIC(MetalMock::Void1StaticFunctions, OverloadedStaticVoid1Function, float, _float)
   METALMOCK_VOID1_STATIC(MetalMock::Void1StaticFunctions, OverloadedStaticVoid1Function, double, _double)

   unique_ptr<MetalMock1Tester<
      Void1FunctionsMock,
      decltype(Void1FunctionMock),
      decltype(Void1FunctionMock_namespace),
      decltype(StaticVoid1FunctionMock),
      decltype(OverloadedStaticVoid1FunctionMock_float)>> _metalMock1Tester;

   STARTUP
   {
      _metalMock1Tester = make_unique<MetalMock1Tester<
         Void1FunctionsMock,
         decltype(Void1FunctionMock),
         decltype(Void1FunctionMock_namespace),
         decltype(StaticVoid1FunctionMock),
         decltype(OverloadedStaticVoid1FunctionMock_float)>>(
         _mock,
         ExpectedVirtualFunctionSignature,
         ExpectedVirtualConstFunctionSignature,
         ExpectedNonVirtualFunctionSignature,
         ExpectedNonVirtualConstFunctionSignature,

         Void1FunctionMock,
         FreeFunctionSignature,

         Void1FunctionMock_namespace,
         ExpectedNamespacedFunctionSignature,

         StaticVoid1FunctionMock,
         StaticFunctionSignature,

         OverloadedStaticVoid1FunctionMock_float,
         ExpectedOverloadedStaticFunctionSignatureA);
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0);
      };
      test(_mock.VirtualFunctionMock);
      test(_mock.VirtualConstFunctionMock);
      test(_mock.NonVirtualFunctionMock);
      test(_mock.NonVirtualConstFunctionMock);

      test(Void1FunctionMock);
      test(Void1FunctionMock_namespace);
      test(StaticVoid1FunctionMock);
      test(OverloadedStaticVoid1FunctionMock_float);
   }

   RUN_TESTS(MetalMockVoid1Tests)
}
