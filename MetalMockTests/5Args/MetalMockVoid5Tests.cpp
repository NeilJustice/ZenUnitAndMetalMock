#include "pch.h"
#include "MetalMockTests/5Args/MetalMock5ArgsTester.h"

void FreeVoid5ArgsFunction(int, int, int, int, int) {}

namespace MetalMock
{
   class Void5ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int, int, int, int) {}
      virtual void VirtualFunctionConst(int, int, int, int, int) const {}
      void NonVirtualFunction(int, int, int, int, int) {}
      void NonVirtualFunctionConst(int, int, int, int, int) const {}
      static void StaticVoid5ArgsFunction(int, int, int, int, int) {}
      virtual ~Void5ArgsFunctions() = default;
   };

   class Void5ArgsFunctionsMock : public Metal::Mock<Void5ArgsFunctions>
   {
   public:
      METALMOCK_VOID5(VirtualFunction, int, int, int, int, int)
      METALMOCK_VOID5_CONST(VirtualFunctionConst, int, int, int, int, int)
      METALMOCK_VOID5_NONVIRTUAL(NonVirtualFunction, int, int, int, int, int)
      METALMOCK_VOID5_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int, int, int, int)
   };

   TESTS(MetalMockVoid5Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(CalledWith_FunctionCalledOnce_ThrowsException)
   AFACT(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   AFACT(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   AFACT(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   AFACT(CalledOnceWith_CalledTwice_ThrowsException)
   EVIDENCE

   Void5ArgsFunctionsMock _void5ArgsFunctionsMock;
   METALMOCK_VOID5_FREE(_call_FreeVoid5ArgsFunction, int, int, int, int, int)
   METALMOCK_VOID5_STATIC(MetalMock::Void5ArgsFunctions, _call_StaticVoid5ArgsFunction, int, int, int, int, int)

   unique_ptr<MetalMock5ArgsTester<
      Void5ArgsFunctionsMock,
      decltype(_call_FreeVoid5ArgsFunctionMock),
      decltype(_call_StaticVoid5ArgsFunctionMock)>> _metalMock5ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void5ArgsFunctions::VirtualFunction(int, int, int, int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void5ArgsFunctions::VirtualFunctionConst(int, int, int, int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void5ArgsFunctions::NonVirtualFunction(int, int, int, int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void5ArgsFunctions::NonVirtualFunctionConst(int, int, int, int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid5ArgsFunction(int, int, int, int, int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void5ArgsFunctions::_call_StaticVoid5ArgsFunction(int, int, int, int, int)";

   STARTUP
   {
      _metalMock5ArgsTester = make_unique<MetalMock5ArgsTester<
         Void5ArgsFunctionsMock, decltype(_call_FreeVoid5ArgsFunctionMock), decltype(_call_StaticVoid5ArgsFunctionMock)>>(
         _void5ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid5ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid5ArgsFunctionMock,
         StaticFunctionSignature);
   }

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock5ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock5ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock5ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock5ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledOnce_ThrowsException)
   {
      _metalMock5ArgsTester->CalledWith_FunctionCalledOnce_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   {
      _metalMock5ArgsTester->CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   {
      _metalMock5ArgsTester->CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly();
   }

   TEST(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   {
      _metalMock5ArgsTester->CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0, 0, 0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0, 0, 0, 0);
      };
      test(_void5ArgsFunctionsMock.VirtualFunctionMock);
      test(_void5ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void5ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void5ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid5ArgsFunctionMock);
      test(_call_StaticVoid5ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void5ArgsFunctions void5ArgsFunctions;
      void5ArgsFunctions.VirtualFunction(0, 0, 0, 0, 0);
      void5ArgsFunctions.VirtualFunctionConst(0, 0, 0, 0, 0);
      void5ArgsFunctions.NonVirtualFunction(0, 0, 0, 0, 0);
      void5ArgsFunctions.NonVirtualFunctionConst(0, 0, 0, 0, 0);
      FreeVoid5ArgsFunction(0, 0, 0, 0, 0);
      MetalMock::Void5ArgsFunctions::StaticVoid5ArgsFunction(0, 0, 0, 0, 0);
   }

   TEST(CalledOnceWith_CalledTwice_ThrowsException)
   {
      _metalMock5ArgsTester->CalledOnceWith_CalledTwice_ThrowsException();
   }

   RUN_TESTS(MetalMockVoid5Tests)
}
