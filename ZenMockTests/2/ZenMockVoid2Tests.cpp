#include "pch.h"
#include "ZenMockTests/2/ZenMock2Tester.h"

void Void2FreeFunction(int, int) {}

namespace ZenMock
{
   struct Void2Functions
   {
      virtual void VirtualFunction(int, int) {}
      virtual void VirtualConstFunction(int, int) const {}
      void NonVirtualFunction(int, int) {}
      void NonVirtualConstFunction(int, int) const {}
      virtual ~Void2Functions() = default;
   };

   struct Void2FunctionsMock : public Zen::Mock<Void2Functions>
   {
      ZENMOCK_VOID2(VirtualFunction, int, int)
      ZENMOCK_VOID2_CONST(VirtualConstFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL(NonVirtualFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualConstFunction, int, int)
   };

   void Void2FreeFunction(int, int) {}

   struct Void2StaticFunctions
   {
      static void StaticVoid2Function(int, int) {}
   };

   TESTS(ZenMockVoid2Tests)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   EVIDENCE

   const string ExpectedVirtualFunctionSignature =
      "virtual void ZenMock::Void2Functions::VirtualFunction(int, int)";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void ZenMock::Void2Functions::VirtualConstFunction(int, int) const";
   const string ExpectedNonVirtualFunctionSignature =
      "void ZenMock::Void2Functions::NonVirtualFunction(int, int)";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void ZenMock::Void2Functions::NonVirtualConstFunction(int, int) const";

   const string ExpectedFreeFunctionSignature =
      "void ::Void2FreeFunction(int, int)";

   const string ExpectedNamespacedFreeFunctionSignature =
      "void ZenMock::Void2FreeFunction(int, int)";

   const string ExpectedStaticFunctionSignature =
      "void ZenMock::Void2StaticFunctions::StaticFunction(int, int)";

   Void2FunctionsMock _zenMockObject;
   ZENMOCK_VOID2_FREE(Void2FreeFunction, int, int)
   ZENMOCK_VOID2_NAMESPACED_FREE(ZenMock, Void2FreeFunction, int, int, _namespaced)
   ZENMOCK_VOID2_STATIC(ZenMock::Void2StaticFunctions, StaticVoid2Function, int, int)

   unique_ptr<ZenMock2Tester<
      Void2FunctionsMock,
      decltype(Void2FreeFunction_ZenMockObject),
      decltype(Void2FreeFunction_ZenMockObject_namespaced),
      decltype(StaticVoid2Function_ZenMockObject)>> _zenMock2Tester;

   STARTUP
   {
      _zenMock2Tester = make_unique<ZenMock2Tester<
         Void2FunctionsMock,
         decltype(Void2FreeFunction_ZenMockObject),
         decltype(Void2FreeFunction_ZenMockObject_namespaced),
         decltype(StaticVoid2Function_ZenMockObject)>>(

         _zenMockObject,

         ExpectedVirtualFunctionSignature,
         ExpectedVirtualConstFunctionSignature,
         ExpectedNonVirtualFunctionSignature,
         ExpectedNonVirtualConstFunctionSignature,

         Void2FreeFunction_ZenMockObject,
         ExpectedFreeFunctionSignature,

         Void2FreeFunction_ZenMockObject_namespaced,
         ExpectedNamespacedFreeFunctionSignature,

         StaticVoid2Function_ZenMockObject,
         ExpectedStaticFunctionSignature);
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject)
      {
         zenMockObject.Expect();
         zenMockObject.Expect();
         zenMockObject.ZenMockIt(0, 0);
         zenMockObject.Expect();
         zenMockObject.CalledOnceWith(0, 0);
      };
      testcase(_zenMockObject.VirtualFunctionMock);
      testcase(_zenMockObject.VirtualConstFunctionMock);
      testcase(_zenMockObject.NonVirtualFunctionMock);
      testcase(_zenMockObject.NonVirtualConstFunctionMock);

      testcase(Void2FreeFunction_ZenMockObject);
      testcase(Void2FreeFunction_ZenMockObject_namespaced);
      testcase(StaticVoid2Function_ZenMockObject);
   }

   RUN_TESTS(ZenMockVoid2Tests)
}
