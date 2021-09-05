#include "pch.h"
#include "MetalMockTests/6Args/MetalMock6ArgsTester.h"

void FreeVoid6ArgsFunction(int, int, int, int, int, int) {}

namespace MetalMock
{
   class Void6ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int, int, int, int, int) {}
      virtual void VirtualFunctionConst(int, int, int, int, int, int) const {}
      void NonVirtualFunction(int, int, int, int, int, int) {}
      void NonVirtualFunctionConst(int, int, int, int, int, int) const {}
      static void StaticVoid6ArgsFunction(int, int, int, int, int, int) {}
      virtual ~Void6ArgsFunctions() = default;
   };

   class Void6ArgsFunctionsMock : public Metal::Mock<Void6ArgsFunctions>
   {
   public:
      METALMOCK_VOID6(VirtualFunction, int, int, int, int, int, int)
      METALMOCK_VOID6_CONST(VirtualFunctionConst, int, int, int, int, int, int)
      METALMOCK_VOID6_NONVIRTUAL(NonVirtualFunction, int, int, int, int, int, int)
      METALMOCK_VOID6_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int, int, int, int, int)
   };

   TESTS(MetalMockVoid6Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   EVIDENCE

   Void6ArgsFunctionsMock _void6ArgsFunctionsMock;
   METALMOCK_VOID6_FREE(_call_FreeVoid6ArgsFunction, int, int, int, int, int, int)
   METALMOCK_VOID6_STATIC(MetalMock::Void6ArgsFunctions, _call_StaticVoid6ArgsFunction, int, int, int, int, int, int)

   unique_ptr<MetalMock6ArgsTester<
      Void6ArgsFunctionsMock,
      decltype(_call_FreeVoid6ArgsFunctionMock),
      decltype(_call_StaticVoid6ArgsFunctionMock)>> _metalMock6ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void6ArgsFunctions::VirtualFunction(int, int, int, int, int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void6ArgsFunctions::VirtualFunctionConst(int, int, int, int, int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void6ArgsFunctions::NonVirtualFunction(int, int, int, int, int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void6ArgsFunctions::NonVirtualFunctionConst(int, int, int, int, int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid6ArgsFunction(int, int, int, int, int, int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void6ArgsFunctions::_call_StaticVoid6ArgsFunction(int, int, int, int, int, int)";

   STARTUP
   {
      _metalMock6ArgsTester = make_unique<MetalMock6ArgsTester<
         Void6ArgsFunctionsMock, decltype(_call_FreeVoid6ArgsFunctionMock), decltype(_call_StaticVoid6ArgsFunctionMock)>>(
         _void6ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid6ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid6ArgsFunctionMock,
         StaticFunctionSignature);
   }

   // MetalMock1ArgTester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock6ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock6ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock6ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock6ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0, 0, 0, 0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0, 0, 0, 0, 0);
      };
      test(_void6ArgsFunctionsMock.VirtualFunctionMock);
      test(_void6ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void6ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void6ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid6ArgsFunctionMock);
      test(_call_StaticVoid6ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void6ArgsFunctions void6ArgsFunctions;
      void6ArgsFunctions.VirtualFunction(0, 0, 0, 0, 0, 0);
      void6ArgsFunctions.VirtualFunctionConst(0, 0, 0, 0, 0, 0);
      void6ArgsFunctions.NonVirtualFunction(0, 0, 0, 0, 0, 0);
      void6ArgsFunctions.NonVirtualFunctionConst(0, 0, 0, 0, 0, 0);
      FreeVoid6ArgsFunction(0, 0, 0, 0, 0, 0);
      MetalMock::Void6ArgsFunctions::StaticVoid6ArgsFunction(0, 0, 0, 0, 0, 0);
   }

   RUN_TESTS(MetalMockVoid6Tests)
}
