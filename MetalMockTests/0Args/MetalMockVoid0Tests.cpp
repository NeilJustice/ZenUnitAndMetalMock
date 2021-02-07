#include "pch.h"
#include "MetalMockTests/0Args/MetalMock0ArgsTester.h"

void GlobalVoid0FreeFunction() {}

namespace MetalMock
{
   class Void0Functions
   {
   public:
      static void StaticVoid0Function() {}
      virtual void VirtualFunction() {}
      virtual void VirtualFunctionConst() const {}
      void NonVirtualFunction() {}
      void NonVirtualFunctionConst() const {}
      virtual ~Void0Functions() = default;
   };

   class Void0FunctionsMock : public Metal::Mock<Void0Functions>
   {
   public:
      METALMOCK_VOID0(VirtualFunction)
      METALMOCK_VOID0_CONST(VirtualFunctionConst)
      METALMOCK_VOID0_NONVIRTUAL(NonVirtualFunction)
      METALMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualFunctionConst)
   };

   TESTS(MetalMockVoid0Tests)
   AFACT(OneHundredPercentCodeCoverage)
   // MetalMock::ZeroArgumentMetalMocker Tests
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   AFACT(MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled)
   AFACT(Expect_MakesMetalMockedFunctionNotThrow_MakesCalledOnceNotThrow_MakesCalledNTimesNotThrow)
   AFACT(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   // MetalMock::VoidZeroArgumentMetalMocker Tests
   AFACT(Expect_MakesMetalMockedFunctionCallNotThrowWhenCalled_ExpectCanBeCalledTwice)
   EVIDENCE

   const string GlobalFreeFunctionSignature =
      "void GlobalVoid0FreeFunction()";
   const string StaticFunctionSignature =
      "void MetalMock::Void0Functions::StaticVoid0Function()";

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void0Functions::VirtualFunction()";
   const string VirtualConstFunctionSignature =
      "virtual void MetalMock::Void0Functions::VirtualFunctionConst() const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void0Functions::NonVirtualFunction()";
   const string NonVirtualConstFunctionSignature =
      "void MetalMock::Void0Functions::NonVirtualFunctionConst() const";

   METALMOCK_VOID0_FREE(GlobalVoid0FreeFunction)
   METALMOCK_VOID0_STATIC(MetalMock::Void0Functions, StaticVoid0Function)
   Void0FunctionsMock _metalMockObject;

   using MetalMock0ArgsTesterType = MetalMock0ArgsTester<
      decltype(GlobalVoid0FreeFunctionMock),
      decltype(StaticVoid0FunctionMock),
      Void0FunctionsMock>;
   unique_ptr<MetalMock0ArgsTesterType> _metalMock0ArgsTester;

   STARTUP
   {
      _metalMock0ArgsTester = make_unique<MetalMock0ArgsTesterType>(
         GlobalVoid0FreeFunctionMock,
         GlobalFreeFunctionSignature,
         StaticVoid0FunctionMock,
         StaticFunctionSignature,
         _metalMockObject,
         VirtualFunctionSignature,
         VirtualConstFunctionSignature,
         NonVirtualFunctionSignature,
         NonVirtualConstFunctionSignature);
   }

   TEST(OneHundredPercentCodeCoverage)
   {
      GlobalVoid0FreeFunction();
      MetalMock::Void0Functions::StaticVoid0Function();

      MetalMock::Void0Functions void0Functions;
      void0Functions.VirtualFunction();
      void0Functions.VirtualFunctionConst();
      void0Functions.NonVirtualFunction();
      void0Functions.NonVirtualFunctionConst();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock0ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   {
      _metalMock0ArgsTester->CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly();
   }

   TEST(MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled)
   {
      _metalMock0ArgsTester->MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled();
   }

   TEST(Expect_MakesMetalMockedFunctionNotThrow_MakesCalledOnceNotThrow_MakesCalledNTimesNotThrow)
   {
      _metalMock0ArgsTester->Expect_MakesMetalMockedFunctionNotThrow_MakesCalledOnceNotThrow_MakesCalledNTimesNotThrow();
   }

   TEST(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   {
      _metalMock0ArgsTester->ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage();
   }

   // MetalMock::VoidZeroArgumentMetalMocker Tests

   TEST(Expect_MakesMetalMockedFunctionCallNotThrowWhenCalled_ExpectCanBeCalledTwice)
   {
      const auto metalmocktest = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.Expect();
         //
         metalMockObject.MetalMockIt();
         //
         metalMockObject.CalledOnce();
      };
      metalmocktest(GlobalVoid0FreeFunctionMock);
      metalmocktest(StaticVoid0FunctionMock);

      metalmocktest(_metalMockObject.VirtualFunctionMock);
      metalmocktest(_metalMockObject.VirtualFunctionConstMock);
      metalmocktest(_metalMockObject.NonVirtualFunctionMock);
      metalmocktest(_metalMockObject.NonVirtualFunctionConstMock);
   }

   RUN_TESTS(MetalMockVoid0Tests)
}
