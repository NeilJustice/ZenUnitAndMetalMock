#include "pch.h"
#include "MetalMockTests/0Args/MetalMock0ArgsTester.h"

void FreeVoid0ArgFunction() {}

namespace MetalMock
{
   class Void0ArgFunctions
   {
   public:
      virtual void VirtualFunction() {}
      virtual void VirtualFunctionConst() const {}
      void NonVirtualFunction() {}
      void NonVirtualFunctionConst() const {}
      static void StaticVoid0ArgFunction() {}
      virtual ~Void0ArgFunctions() = default;
   };

   class Void0ArgFunctionsMock : public Metal::Mock<Void0ArgFunctions>
   {
   public:
      METALMOCK_VOID0(VirtualFunction)
      METALMOCK_VOID0_CONST(VirtualFunctionConst)
      METALMOCK_VOID0_NONVIRTUAL(NonVirtualFunction)
      METALMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualFunctionConst)
   };

   TESTS(MetalMockVoid0Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   AFACT(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   AFACT(CalledOnce_ExpectedFunctionCalledOnce_DoesNotThrowException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   EVIDENCE

   Void0ArgFunctionsMock _void0ArgFunctionsMock;
   METALMOCK_VOID0_FREE(_call_FreeVoid0ArgFunction)
   METALMOCK_VOID0_STATIC(MetalMock::Void0ArgFunctions, _call_StaticVoid0ArgFunction)

   unique_ptr<MetalMock0ArgsTester<
      Void0ArgFunctionsMock,
      decltype(_call_FreeVoid0ArgFunctionMock),
      decltype(_call_StaticVoid0ArgFunctionMock)>> _metalMock0ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void0ArgFunctions::VirtualFunction()";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void0ArgFunctions::VirtualFunctionConst() const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void0ArgFunctions::NonVirtualFunction()";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void0ArgFunctions::NonVirtualFunctionConst() const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid0ArgFunction()";
   const string StaticFunctionSignature =
      "void MetalMock::Void0ArgFunctions::_call_StaticVoid0ArgFunction()";

   STARTUP
   {
      _metalMock0ArgsTester = make_unique<MetalMock0ArgsTester<
         Void0ArgFunctionsMock, decltype(_call_FreeVoid0ArgFunctionMock), decltype(_call_StaticVoid0ArgFunctionMock)>>(
         _void0ArgFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid0ArgFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid0ArgFunctionMock,
         StaticFunctionSignature);
   }

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock0ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   {
      _metalMock0ArgsTester->ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled();
   }

   TEST(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   {
      _metalMock0ArgsTester->MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow();
   }

   TEST(CalledOnce_ExpectedFunctionCalledOnce_DoesNotThrowException)
   {
      _metalMock0ArgsTester->CalledOnce_ExpectedFunctionCalledOnce_DoesNotThrowException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock0ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock0ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock0ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt();
         metalMockObject.Expect();
         metalMockObject.CalledOnce();
      };
      test(_void0ArgFunctionsMock.VirtualFunctionMock);
      test(_void0ArgFunctionsMock.VirtualFunctionConstMock);
      test(_void0ArgFunctionsMock.NonVirtualFunctionMock);
      test(_void0ArgFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid0ArgFunctionMock);
      test(_call_StaticVoid0ArgFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void0ArgFunctions void0Functions;
      void0Functions.VirtualFunction();
      void0Functions.VirtualFunctionConst();
      void0Functions.NonVirtualFunction();
      void0Functions.NonVirtualFunctionConst();
      FreeVoid0ArgFunction();
      MetalMock::Void0ArgFunctions::StaticVoid0ArgFunction();
   }

   RUN_TESTS(MetalMockVoid0Tests)
}
