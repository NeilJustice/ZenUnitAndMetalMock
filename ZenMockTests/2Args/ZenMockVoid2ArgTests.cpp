#include "pch.h"
#include "ZenMockTests/2Args/ZenMock2ArgTester.h"

void Void2ArgFreeFunction(int, int) {}

namespace ZenMock
{
   struct Void2ArgFunctions
   {
      virtual void VirtualFunction(int, int) {}
      virtual void VirtualConstFunction(int, int) const {}
      void NonVirtualFunction(int, int) {}
      void NonVirtualConstFunction(int, int) const {}
      virtual ~Void2ArgFunctions() = default;
   };

   struct Void2ArgFunctionsMock : public Zen::Mock<Void2ArgFunctions>
   {
      ZENMOCK_VOID2(VirtualFunction, int, int)
      ZENMOCK_VOID2_CONST(VirtualConstFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL(NonVirtualFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualConstFunction, int, int)
   };

   void Void2ArgFreeFunction(int, int) {}

   struct Void2ArgStaticFunctions
   {
      static void StaticVoid2ArgFunction(int, int) {}
   };

   TESTS(ZenMockVoid2ArgTests)
   AFACT(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   EVIDENCE

   Void2ArgFunctionsMock _zenMockObject;
   ZENMOCK_VOID2_FREE(Void2ArgFreeFunction, int, int)
   ZENMOCK_VOID2_NAMESPACED_FREE(ZenMock, Void2ArgFreeFunction, int, int, _namespaced)
   ZENMOCK_VOID2_STATIC(ZenMock::Void2ArgStaticFunctions, StaticVoid2ArgFunction, int, int)

   unique_ptr<ZenMock2ArgTester<
      Void2ArgFunctionsMock,
      decltype(Void2ArgFreeFunction_ZenMockObject),
      decltype(Void2ArgFreeFunction_ZenMockObject_namespaced),
      decltype(StaticVoid2ArgFunction_ZenMockObject)>> _zenMock2ArgTester;

   const string ExpectedVirtualFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::VirtualFunction(int, int)";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::VirtualConstFunction(int, int) const";
   const string ExpectedNonVirtualFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtualFunction(int, int)";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtualConstFunction(int, int) const";
   const string ExpectedFreeFunctionSignature =
      "void ::Void2ArgFreeFunction(int, int)";
   const string ExpectedNamespacedFreeFunctionSignature =
      "void ZenMock::Void2ArgFreeFunction(int, int)";
   const string ExpectedStaticFunctionSignature =
      "void ZenMock::Void2ArgStaticFunctions::StaticFunction(int, int)";

   STARTUP
   {
      _zenMock2ArgTester = make_unique<ZenMock2ArgTester<
         Void2ArgFunctionsMock,
         decltype(Void2ArgFreeFunction_ZenMockObject),
         decltype(Void2ArgFreeFunction_ZenMockObject_namespaced),
         decltype(StaticVoid2ArgFunction_ZenMockObject)>>(
         _zenMockObject,

         ExpectedVirtualFunctionSignature,
         ExpectedVirtualConstFunctionSignature,
         ExpectedNonVirtualFunctionSignature,
         ExpectedNonVirtualConstFunctionSignature,

         Void2ArgFreeFunction_ZenMockObject,
         ExpectedFreeFunctionSignature,

         Void2ArgFreeFunction_ZenMockObject_namespaced,
         ExpectedNamespacedFreeFunctionSignature,

         StaticVoid2ArgFunction_ZenMockObject,
         ExpectedStaticFunctionSignature);
   }

   TEST(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
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

      testcase(Void2ArgFreeFunction_ZenMockObject);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced);
      testcase(StaticVoid2ArgFunction_ZenMockObject);
   }

   RUN_TESTS(ZenMockVoid2ArgTests)
}
