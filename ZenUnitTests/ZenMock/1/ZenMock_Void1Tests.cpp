#include "pch.h"
#include "ZenMock1Tester.h"

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
      //const auto test = [](auto& zenMockObject)
      //{
      //   zenMockObject.Expect();
      //   zenMockObject.Expect();
      //};
      //test(_mock.VirtualFunctionMock);
      //test(_mock.VirtualConstFunctionMock);
      //test(_mock.NonVirtualFunctionMock);
      //test(_mock.NonVirtualConstFunctionMock);
      //test(Void1Function_ZenMock);
      //test(Void1Function_ZenMock_namespace);
      //test(StaticVoid1Function_ZenMock);
      //test(OverloadedStaticVoid1Function_ZenMock_float);
   }

   }; RUNTESTS(ZenMock_Void1Tests)
}
