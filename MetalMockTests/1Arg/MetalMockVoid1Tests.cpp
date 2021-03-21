#include "pch.h"
#include "MetalMockTests/1Arg/MetalMock1Tester.h"

void FreeVoid1ArgFunction(int) {}

namespace MetalMock
{
   class Void1Functions
   {
   public:
      virtual void VirtualFunction(int) {}
      virtual void VirtualConstFunction(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualConstFunction(int) const {}
      virtual ~Void1Functions() = default;
   };

   class Void1FunctionsMock : public Metal::Mock<Void1Functions>
   {
   public:
      METALMOCK_VOID1(VirtualFunction, int)
      METALMOCK_VOID1_CONST(VirtualConstFunction, int)
      METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualConstFunction, int)
   };

   class Void1StaticFunctions
   {
   public:
      static void StaticVoid1Function(int) {}
   };

   TESTS(MetalMockVoid1Tests)
   // MetalMock1Tester Tests
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   // MetalMockVoid1Tests
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctionsCodeCoverage)
   EVIDENCE

   Void1FunctionsMock _void1FunctionsMock;
   METALMOCK_VOID1_FREE(FreeVoid1ArgFunction, int)
   METALMOCK_VOID1_STATIC(MetalMock::Void1StaticFunctions, StaticVoid1Function, int)

   unique_ptr<MetalMock1Tester<
      Void1FunctionsMock,
      decltype(FreeVoid1ArgFunctionMock),
      decltype(StaticVoid1FunctionMock)>> _metalMock1Tester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void1Functions::VirtualFunction(int)";
   const string VirtualConstFunctionSignature =
      "virtual void MetalMock::Void1Functions::VirtualConstFunction(int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void1Functions::NonVirtualFunction(int)";
   const string NonVirtualConstFunctionSignature =
      "void MetalMock::Void1Functions::NonVirtualConstFunction(int) const";
   const string FreeFunctionSignature =
      "void FreeVoid1ArgFunction(int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void1StaticFunctions::StaticVoid1Function(int)";

   STARTUP
   {
      _metalMock1Tester = make_unique<MetalMock1Tester<
         Void1FunctionsMock, decltype(FreeVoid1ArgFunctionMock), decltype(StaticVoid1FunctionMock)>>(
         _void1FunctionsMock,
         VirtualFunctionSignature,
         VirtualConstFunctionSignature,
         NonVirtualFunctionSignature,
         NonVirtualConstFunctionSignature,
         FreeVoid1ArgFunctionMock,
         FreeFunctionSignature,
         StaticVoid1FunctionMock,
         StaticFunctionSignature);
   }

   // MetalMock1Tester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock1Tester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   // MetalMockVoid1Tests

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0);
      };
      test(_void1FunctionsMock.VirtualFunctionMock);
      test(_void1FunctionsMock.VirtualConstFunctionMock);
      test(_void1FunctionsMock.NonVirtualFunctionMock);
      test(_void1FunctionsMock.NonVirtualConstFunctionMock);
      test(FreeVoid1ArgFunctionMock);
      test(StaticVoid1FunctionMock);
   }

   TEST(MockedFunctionsCodeCoverage)
   {
      MetalMock::Void1Functions void1Functions;
      void1Functions.VirtualFunction(0);
      void1Functions.VirtualConstFunction(0);
      void1Functions.NonVirtualFunction(0);
      void1Functions.NonVirtualConstFunction(0);
      FreeVoid1ArgFunction(0);
      MetalMock::Void1StaticFunctions::StaticVoid1Function(0);
   }

   RUN_TESTS(MetalMockVoid1Tests)
}
