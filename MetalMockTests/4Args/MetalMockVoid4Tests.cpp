#include "pch.h"
#include "MetalMockTests/4Args/MetalMock4ArgsTester.h"

void FreeVoid4ArgsFunction(int, int, int, int) {}

namespace MetalMock
{
   class Void4ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int, int, int) {}
      virtual void VirtualFunctionConst(int, int, int, int) const {}
      void NonVirtualFunction(int, int, int, int) {}
      void NonVirtualFunctionConst(int, int, int, int) const {}
      static void StaticVoid4ArgsFunction(int, int, int, int) {}
      virtual ~Void4ArgsFunctions() = default;
   };

   class Void4ArgsFunctionsMock : public Metal::Mock<Void4ArgsFunctions>
   {
   public:
      METALMOCK_VOID4(VirtualFunction, int, int, int, int)
      METALMOCK_VOID4_CONST(VirtualFunctionConst, int, int, int, int)
      METALMOCK_VOID4_NONVIRTUAL(NonVirtualFunction, int, int, int, int)
      METALMOCK_VOID4_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int, int, int)
   };

   TESTS(MetalMockVoid4Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(CalledWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   AFACT(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   AFACT(CalledWith_FunctionCalledOnceWithMismatchingArg_ThrowsAnomaly)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   AFACT(CalledWith_CalledTwice_ThrowsException)
   AFACT(CalledOnceWith_CalledTwice_ThrowsException)
   AFACT(CalledAsFollows_CalledTwice_ThrowsException)
   EVIDENCE

   Void4ArgsFunctionsMock _void4ArgsFunctionsMock;
   METALMOCK_VOID4_FREE(_call_FreeVoid4ArgsFunction, int, int, int, int)
   METALMOCK_VOID4_STATIC(MetalMock::Void4ArgsFunctions, _call_StaticVoid4ArgsFunction, int, int, int, int)

   unique_ptr<MetalMock4ArgsTester<
      Void4ArgsFunctionsMock,
      decltype(_call_FreeVoid4ArgsFunctionMock),
      decltype(_call_StaticVoid4ArgsFunctionMock)>> _metalMock4ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void4ArgsFunctions::VirtualFunction(int, int, int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void4ArgsFunctions::VirtualFunctionConst(int, int, int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void4ArgsFunctions::NonVirtualFunction(int, int, int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void4ArgsFunctions::NonVirtualFunctionConst(int, int, int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid4ArgsFunction(int, int, int, int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void4ArgsFunctions::_call_StaticVoid4ArgsFunction(int, int, int, int)";

   STARTUP
   {
      _metalMock4ArgsTester = make_unique<MetalMock4ArgsTester<
         Void4ArgsFunctionsMock, decltype(_call_FreeVoid4ArgsFunctionMock), decltype(_call_StaticVoid4ArgsFunctionMock)>>(
         _void4ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid4ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid4ArgsFunctionMock,
         StaticFunctionSignature);
   }

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock4ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock4ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock4ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock4ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   {
      _metalMock4ArgsTester->CalledWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   {
      _metalMock4ArgsTester->CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException();
   }

   TEST(CalledWith_FunctionCalledOnceWithMismatchingArg_ThrowsAnomaly)
   {
      _metalMock4ArgsTester->CalledWith_FunctionCalledOnceWithMismatchingArg_ThrowsAnomaly();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0, 0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0, 0, 0);
      };
      test(_void4ArgsFunctionsMock.VirtualFunctionMock);
      test(_void4ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void4ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void4ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid4ArgsFunctionMock);
      test(_call_StaticVoid4ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void4ArgsFunctions void4ArgsFunctions;
      void4ArgsFunctions.VirtualFunction(0, 0, 0, 0);
      void4ArgsFunctions.VirtualFunctionConst(0, 0, 0, 0);
      void4ArgsFunctions.NonVirtualFunction(0, 0, 0, 0);
      void4ArgsFunctions.NonVirtualFunctionConst(0, 0, 0, 0);
      FreeVoid4ArgsFunction(0, 0, 0, 0);
      MetalMock::Void4ArgsFunctions::StaticVoid4ArgsFunction(0, 0, 0, 0);
   }

   TEST(CalledWith_CalledTwice_ThrowsException)
   {
      _metalMock4ArgsTester->CalledWith_CalledTwice_ThrowsException();
   }

   TEST(CalledOnceWith_CalledTwice_ThrowsException)
   {
      _metalMock4ArgsTester->CalledOnceWith_CalledTwice_ThrowsException();
   }

   TEST(CalledAsFollows_CalledTwice_ThrowsException)
   {
      _metalMock4ArgsTester->CalledAsFollows_CalledTwice_ThrowsException();
   }

   RUN_TESTS(MetalMockVoid4Tests)
}
